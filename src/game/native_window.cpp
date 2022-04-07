#include "native_window.h"
#include <cassert>
#include "../editor/window.h"
#include "../log.h"
#include "SDL.h"
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_sdlrenderer.h"

namespace pal {

NativeWindow::NativeWindow(int width, int height, const std::string& title)
    : _title(title), _width(width), _height(height) {
  _window = SDL_CreateWindow(_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _width,
                             _height, SDL_WINDOW_OPENGL);
  assert(_window && "create window failed !");
  _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
  assert(_renderer && "create renderer failed !");
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
}

NativeWindow::~NativeWindow() {
  ImGui_ImplSDLRenderer_Shutdown();
  ImGui_ImplSDL2_Shutdown();
  ImGui::DestroyContext();

  SDL_DestroyWindow(_window);
  _window = nullptr;
}

void NativeWindow::renderImGui() {
  for (auto pair : _imgui_windows) {
    pair.second->render();
  }
}

void NativeWindow::present() { SDL_RenderPresent(_renderer); }

void NativeWindow::erase(int r, int g, int b, int a) {
  SDL_SetRenderDrawColor(_renderer, (Uint8)r, (Uint8)g, (Uint8)b, (Uint8)a);
  SDL_RenderClear(_renderer);
}

}  // namespace pal
