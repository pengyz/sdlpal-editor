#include "game_renderer.h"
#include <array>
#include "../engine/engine.h"
#include "../log.h"
#include "render/sdl2_backend.h"

namespace engine {

GameRenderer::GameRenderer(SDL_Renderer* renderer) : _renderer(renderer) {}

GameRenderer::~GameRenderer() {
  if (_backend) {
    delete _backend;
    _backend = nullptr;
  }
}

bool GameRenderer::init(int width, int height) {
  //创建逻辑texture
  _backend = new render::SDL2_Backend(_renderer, true);
  _backend->Setup();
  _backend->CreateTexture(width, height);
  _backend->palette(SDL_AllocPalette(256));
  return true;
}

SDL_Texture* GameRenderer::texture() { return _backend->texture(); }

void GameRenderer::fillRect(SDL_Colour color, const SDL_Rect& rect) {
  SDL_SetRenderTarget(_backend->renderer(), _backend->texture());
  SDL_SetRenderDrawColor(_backend->renderer(), color.r, color.g, color.b, color.a);
  SDL_RenderFillRect(_backend->renderer(), &rect);
  SDL_SetRenderTarget(_backend->renderer(), nullptr);
}

SDL_Color* GameRenderer::getPalette(int32_t iPaletteNum, bool fNight) {
  std::array<uint8_t, 1536> buf;
  //   INT i;

  MKFFile _pat;
  if (!Engine::get()->loadMKFFile("pat.mkf", _pat)) {
    LOG(ERROR) << "load pat.mkf failed !";
    return nullptr;
  }

  // Read the palette data from the pat.mkf file
  int32_t i = _pat.readChunk(&buf[0], buf.size(), iPaletteNum);
  _pat.close();

  if (i < 0) {
    // Read failed
    return nullptr;
  } else if (i <= 256 * 3) {
    // There is no night colors in the palette
    fNight = false;
  }

  for (i = 0; i < 256; i++) {
    _paletteColors[i].r = buf[(fNight ? 256 * 3 : 0) + i * 3] << 2;
    _paletteColors[i].g = buf[(fNight ? 256 * 3 : 0) + i * 3 + 1] << 2;
    _paletteColors[i].b = buf[(fNight ? 256 * 3 : 0) + i * 3 + 2] << 2;
#if 0
      _paletteColors[i].r += (255 - _paletteColors[i].r) / 5;
      _paletteColors[i].g += (255 - _paletteColors[i].g) / 5;
      _paletteColors[i].b += (255 - _paletteColors[i].b) / 5;
#endif
  }

  return &_paletteColors[0];
}

void GameRenderer::setPalette(SDL_Color rgPalette[256]) {
  SDL_Rect rect;

  SDL_SetPaletteColors(_palette, rgPalette, 0, 256);

  // SDL_SetSurfacePalette(gpScreen, _palette);
  // SDL_SetSurfacePalette(gpScreenBak, _palette);

  // //
  // // HACKHACK: need to invalidate gpScreen->map otherwise the palette
  // // would not be effective during blit
  // //
  // SDL_SetSurfaceColorMod(gpScreen, 0, 0, 0);
  // SDL_SetSurfaceColorMod(gpScreen, 0xFF, 0xFF, 0xFF);
  // SDL_SetSurfaceColorMod(gpScreenBak, 0, 0, 0);
  // SDL_SetSurfaceColorMod(gpScreenBak, 0xFF, 0xFF, 0xFF);

  rect.x = 0;
  rect.y = 0;
  rect.w = 320;
  rect.h = 200;

  // VIDEO_UpdateScreen(&rect);
}

}  // namespace engine
