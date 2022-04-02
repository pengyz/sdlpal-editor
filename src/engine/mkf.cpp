#include "mkf.h"
#include <SDL.h>
#include <cassert>
#include "engine.h"
#include "yj1.h"

namespace engine {

#define PAL_fread(buf) \
  ifs >> buf;          \
  if (ifs.fail()) return -1;

MKFFile::MKFFile() {}

MKFFile::MKFFile(const std::filesystem::path& path) {
  ifs = std::ifstream(path);
}

MKFFile::~MKFFile() { close(); }
MKFFile::MKFFile(MKFFile&& other) { ifs = std::move(other.ifs); }

MKFFile& MKFFile::operator=(MKFFile&& other) {
  ifs = std::move(other.ifs);
  return *this;
}

bool MKFFile::open(const std::filesystem::path& path) {
  ifs.open(path);
  if (ifs.fail()) return false;
  return true;
}

bool MKFFile::is_open() { return ifs.is_open(); }

void MKFFile::close() {
  if (ifs.is_open()) ifs.close();
}

uint32_t MKFFile::getChunkCount() {
  assert(ifs.is_open() && "please open file first !");
  uint32_t iNumChunk = 0;
  ifs.seekg(0);
  ifs >> iNumChunk;
  if (ifs.fail()) {
    return 0u;
  }
  return (SDL_SwapLE32(iNumChunk) - 4) >> 2;
}

uint32_t MKFFile::getChunkSize(int32_t uiChunkNum) {
  assert(ifs.is_open() && "please open file first !");

  uint32_t uiOffset = 0;
  uint32_t uiNextOffset = 0;

  //
  // Get the total number of chunks.
  //
  uint32_t uiChunkCount = getChunkCount();
  if (uiChunkNum >= uiChunkCount) {
    return -1;
  }

  //
  // Get the offset of the specified chunk and the next chunk.
  //
  ifs.seekg(4 * uiChunkNum);
  PAL_fread(uiOffset);
  PAL_fread(uiNextOffset);

  uiOffset = SDL_SwapLE32(uiOffset);
  uiNextOffset = SDL_SwapLE32(uiNextOffset);

  //
  // Return the length of the chunk.
  //
  return static_cast<int32_t>(uiNextOffset - uiOffset);
}

int32_t MKFFile::readChunk(uint8_t* lpBuffer, uint32_t uiBufferSize, uint32_t uiChunkNum) {
  assert(ifs.is_open() && "please open file first !");

  if (lpBuffer == nullptr || uiBufferSize == 0) {
    return -1;
  }

  //
  // Get the total number of chunks.
  //
  uint32_t uiChunkCount = getChunkCount();
  if (uiChunkNum >= uiChunkCount) {
    return -1;
  }

  //
  // Get the offset of the chunk.
  //
  uint32_t uiOffset = 0;
  uint32_t uiNextOffset = 0;
  ifs.seekg(4 * uiChunkNum);
  PAL_fread(uiOffset);
  PAL_fread(uiNextOffset);
  uiOffset = SDL_SwapLE32(uiOffset);
  uiNextOffset = SDL_SwapLE32(uiNextOffset);

  //
  // Get the length of the chunk.
  //
  uint32_t uiChunkLen = uiNextOffset - uiOffset;

  if (uiChunkLen > uiBufferSize) {
    return -2;
  }

  if (uiChunkLen != 0) {
    ifs.seekg(uiOffset);
    ifs.read((char*)lpBuffer, uiChunkLen);
    return ifs.tellg();
  }

  return -1;
}

int32_t MKFFile::getDecompressedSize(uint32_t uiChunkNum) {
  assert(ifs.is_open() && "please open file first !");
  uint32_t buf[2];

  //
  // Get the total number of chunks.
  //
  uint32_t uiChunkCount = getChunkCount();
  if (uiChunkNum >= uiChunkCount) {
    return -1;
  }

  //
  // Get the offset of the chunk.
  //
  uint32_t uiOffset = 0u;
  ifs.seekg(4 * uiChunkNum);
  PAL_fread(uiOffset);
  uiOffset = SDL_SwapLE32(uiOffset);

  //
  // Read the header.
  //
  ifs.seekg(uiOffset);
  if (Engine::isWin95()) {
    PAL_fread(buf[0]);
    buf[0] = SDL_SwapLE32(buf[0]);

    return (int32_t)buf[0];
  } else {
    PAL_fread(buf[0]);
    PAL_fread(buf[1]);
    buf[0] = SDL_SwapLE32(buf[0]);
    buf[1] = SDL_SwapLE32(buf[1]);

    return (buf[0] != 0x315f4a59) ? -1 : (int32_t)buf[1];
  }
}

int32_t MKFFile::decompressChunk(uint8_t* lpBuffer, uint32_t uiBufferSize, uint32_t uiChunkNum) {
  assert(ifs.is_open() && "please open file first !");
  uint32_t len = getChunkSize(uiChunkNum);

  if (len <= 0) {
    return len;
  }

  uint8_t* buf = (uint8_t*)malloc(len);
  if (buf == nullptr) {
    return -3;
  }

  readChunk(buf, len, uiChunkNum);

  if (Engine::isWin95())
    len = YJ2_Decompress(buf, lpBuffer, uiBufferSize);
  else
    len = YJ1_Decompress(buf, lpBuffer, uiBufferSize);
  free(buf);

  return len;
}

}  // namespace engine
