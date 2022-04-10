#pragma once
#include "render_backend.h"

namespace render {
class SDL2_Backend : public RenderBackend {
 public:
  SDL2_Backend(SDL_Renderer* renderer, bool keepAspectRatio)
      : RenderBackend(renderer, keepAspectRatio, false) {}
  void Init() override;
  void Setup() override;
  SDL_Texture* CreateTexture(int width, int height) override;
  void RenderCopy() override;
};
}  // namespace render