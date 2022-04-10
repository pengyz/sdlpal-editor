#pragma once
#include "SDL.h"

namespace render {
  class RenderBackend;
}

namespace engine {

/**
 * @brief 渲染器
 *
 */
class Renderer {
 public:
  Renderer() = default;
  bool init();
  ~Renderer() = default;

 private:
  SDL_Surface* _logicScreen;
  render::RenderBackend* _backend = nullptr;  //backend
};
}  // namespace engine