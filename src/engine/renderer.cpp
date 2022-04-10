#include "renderer.h"
#include "render/sdl2_backend.h"

namespace engine {
bool Renderer::init() {
  //创建逻辑texture
  _backend = new render::SDL2_Backend(nullptr, true);

  return true;
}
}  // namespace engine
