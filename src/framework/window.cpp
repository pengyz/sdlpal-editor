#include "window.h"
#include <cassert>

Window::Window(int width, int height, const std::string& title) : _title(title) {
  _window = SDL_CreateWindow(_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width,
                             height, SDL_WINDOW_OPENGL);
  assert(_window != nullptr);
}

Window::~Window() {
  if (_window) {
    SDL_DestroyWindow(_window);
    _window = nullptr;
  }
}
