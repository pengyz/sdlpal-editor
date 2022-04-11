#include "renderer.h"
#include "render/sdl2_backend.h"

namespace engine {

Renderer::Renderer(SDL_Renderer* renderer) : _renderer(renderer) {}

Renderer::~Renderer() {
  if (_backend) {
    delete _backend;
    _backend = nullptr;
  }
}

bool Renderer::init(int width, int height) {
  //创建逻辑texture
  _backend = new render::SDL2_Backend(_renderer, true);
  _backend->Setup();
  _backend->CreateTexture(width, height);
  _backend->palette(SDL_AllocPalette(256));
  return true;
}

SDL_Texture* Renderer::texture() { return _backend->texture(); }

}  // namespace engine
