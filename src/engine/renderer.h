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
  Renderer(SDL_Renderer* renderer);
  ~Renderer();
  /**
   * @brief 初始化
   *
   * @param widht
   * @param height
   * @return true
   * @return false
   */
  bool init(int widht, int height);

  /**
   * @brief 获取texuture
   *
   * @return SDL_Texture*
   */
  SDL_Texture* texture();

 private:
  SDL_Surface* _logicScreen;
  render::RenderBackend* _backend = nullptr;  // backend
  SDL_Renderer* _renderer = nullptr;          // renderer
};
}  // namespace engine