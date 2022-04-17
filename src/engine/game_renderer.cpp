#include "game_renderer.h"
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

}  // namespace engine
