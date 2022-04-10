#pragma once
#include "SDL.h"

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
};
}  // namespace engine