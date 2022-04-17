#include "sdl2_backend.h"
#include <cfloat>
#include <cmath>
#include "../../log.h"
#include "SDL.h"

namespace render {

void SDL2_Backend::Init() { LOG(INFO) << "SDL2_Backend::Init()"; }

void SDL2_Backend::Setup() { LOG(INFO) << "SDL2_Backend::Setup()"; }

SDL_Texture *SDL2_Backend::CreateTexture(int width, int height) {
  int texture_width, texture_height;
  double ratio = (double)width / (double)height;
  ratio *= 1.6f * (double)textureHeight() / (float)textureWidth();
  //
  // Check whether to keep the aspect ratio
  //
  if (keepAspectRatio() && fabs(ratio - 1.6f) > FLT_EPSILON) {
    if (ratio > 1.6f) {
      texture_height = 200;
      texture_width = (int)(200 * ratio) & ~0x3;
      ratio = (float)height / 200.0f;
    } else {
      texture_width = 320;
      texture_height = (int)(320 / ratio) & ~0x3;
      ratio = (float)width / 320.0f;
    }

    unsigned short w = (unsigned short)(ratio * 320.0f) & ~0x3;
    unsigned short h = (unsigned short)(ratio * 200.0f) & ~0x3;
    textureRect()->x = (texture_width - 320) / 2;
    textureRect()->y = (texture_height - 200) / 2;
    textureRect()->w = 320;
    textureRect()->h = 200;

    // VIDEO_SetupTouchArea(width, height, w, h);
  } else {
    texture_width = 320;
    texture_height = 200;
    textureRect()->x = textureRect()->y = 0;
    textureRect()->w = 320;
    textureRect()->h = 200;

    // VIDEO_SetupTouchArea(width, height, width, height);
  }

  //
  // Create texture for screen as a render target
  //
  texture(SDL_CreateTexture(renderer(), SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET,
                            texture_width, texture_height));
  return texture();
}

void SDL2_Backend::RenderCopy() {
  // TODO: 不需要copy 使用ImGui Image进行合成
  //   void *texture_pixels;
  //   int texture_pitch;

  //   SDL_LockTexture(texture(), NULL, &texture_pixels, &texture_pitch);
  //   memset(texture_pixels, 0, textureRect()->y * texture_pitch);
  //   uint8_t *pixels = (uint8_t *)texture_pixels + textureRect()->y * texture_pitch;
  //   uint8_t *src = (uint8_t *)gpScreenReal->pixels;
  //   int left_pitch = textureRect()->x << 2;
  //   int right_pitch = texture_pitch - ((textureRect()->x + textureRect()->w) << 2);
  //   for (int y = 0; y < textureRect()->h; y++, src += gpScreenReal->pitch) {
  //     memset(pixels, 0, left_pitch);
  //     pixels += left_pitch;
  //     memcpy(pixels, src, 320 << 2);
  //     pixels += 320 << 2;
  //     memset(pixels, 0, right_pitch);
  //     pixels += right_pitch;
  //   }
  //   memset(pixels, 0, textureRect()->y * texture_pitch);
  //   SDL_UnlockTexture(texture());

  //   SDL_RenderClear(renderer());
  //   SDL_RenderCopy(renderer(), texture(), NULL, NULL);
  //   if (gConfig.fUseTouchOverlay) {
  //     SDL_RenderCopy(renderer(), gpTouchOverlay, NULL, &gOverlayRect);
  //   }
  //   SDL_RenderPresent(renderer());
}

}  // namespace render
