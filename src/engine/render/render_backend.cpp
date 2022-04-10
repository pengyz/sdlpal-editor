#include "render_backend.h"
#include "SDL.h"

namespace render {
RenderBackend::RenderBackend(SDL_Renderer* renderer, bool bKeepAspectRatio)
    : _renderer(renderer), _bKeepAspectRatio(bKeepAspectRatio) {}
RenderBackend::~RenderBackend() {
  if (_textureRect) {
    delete _textureRect;
    _textureRect = nullptr;
  }
}

SDL_Renderer* RenderBackend::renderer() { return _renderer; }
bool RenderBackend::keepAspectRatio() { return _bKeepAspectRatio; }
void RenderBackend::keepAspectRatio(bool val) { _bKeepAspectRatio = val; }
SDL_Rect* RenderBackend::textureRect() { return _textureRect; }
void RenderBackend::textureRect(SDL_Rect* rect) { *_textureRect = *rect; }
int RenderBackend::textureWidth() { return _textureWidth; }
void RenderBackend::textureWidth(int width) { _textureWidth = width; }
int RenderBackend::textureHeight() { return _textureHeight; }
void RenderBackend::textureHeight(int height) { _textureHeight = height; }
SDL_Texture* RenderBackend::texture() { return _texture; }

}  // namespace render