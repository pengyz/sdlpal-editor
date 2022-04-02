#pragma once
#include <filesystem>
#include <fstream>

namespace engine {

/**
 * @brief mkf resource file
 *
 */
class MKFFile {
 public:
  //只允许移动构造
  MKFFile(const MKFFile&) = delete;
  MKFFile& operator=(const MKFFile&) = delete;

  MKFFile();
  MKFFile(const std::filesystem::path& path);

  ~MKFFile();
  MKFFile(MKFFile&& other);
  MKFFile& operator=(MKFFile&& other);

  /**
   * @brief 打开文件
   *
   * @param path
   * @return true
   * @return false
   */
  bool open(const std::filesystem::path& path);

  /**
   * @brief 关闭文件
   *
   */
  void close();

  /**
   * @brief 是否已经打开
   *
   * @return true
   * @return false
   */
  bool is_open();

  operator bool() { return is_open(); }

  /**
   * @brief Get the number of chunks in an MKF archive.
   *
   * @return uint32_t Integer value which indicates the number of chunks in the specified MKF file.
   */
  uint32_t getChunkCount();

  /**
   * @brief Get the size of a chunk in an MKF archive.
   *
   * @param uiChunkNum the number of the chunk in the MKF archive.
   * @return uint32_t     Integer value which indicates the size of the chunk.
   *                      -1 if the chunk does not exist.
   */
  uint32_t getChunkSize(int32_t uiChunkNum);

  /**
   * @brief Read a chunk from an MKF archive into lpBuffer.
   *
   * @param lpBuffer lpBuffer - pointer to the destination buffer.
   * @param uiBufferSize size of the destination buffer.
   * @param uiChunkNum the number of the chunk in the MKF archive to read.
   * @return int32_t Integer value which indicates the size of the chunk.
   *            -1 if there are error in parameters.
   *            -2 if buffer size is not enough.
   */
  int32_t readChunk(uint8_t* lpBuffer, uint32_t uiBufferSize, uint32_t uiChunkNum);

  /**
   * @brief Get the decompressed size of a compressed chunk in an MKF archive.
   *
   * @param uiChunkNum the number of the chunk in the MKF archive.
   * @return int32_t Integer value which indicates the size of the chunk.
   *          -1 if the chunk does not exist.
   */
  int32_t getDecompressedSize(uint32_t uiChunkNum);

  /**
   * @brief Decompress a compressed chunk from an MKF archive into lpBuffer.
   *
   * @param lpBuffer pointer to the destination buffer.
   * @param uiBufferSize size of the destination buffer.
   * @param uiChunkNum the number of the chunk in the MKF archive to read.
   * @return int32_t Integer value which indicates the size of the chunk.
   *          -1 if there are error in parameters, or buffer size is not enough.
   *          -3 if cannot allocate memory for decompression.
   */
  int32_t decompressChunk(uint8_t* lpBuffer, uint32_t uiBufferSize, uint32_t uiChunkNum);

 private:
  std::ifstream ifs;
};

}  // namespace engine
