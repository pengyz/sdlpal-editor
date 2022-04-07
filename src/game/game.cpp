#include "game.h"
#include <SDL.h>
#include <cassert>
#include "../editor/editor_window.h"
#include "../log.h"
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_sdlrenderer.h"
#include "native_window.h"

namespace pal {

Game::Game() {
  int ret = SDL_Init(SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS);
  assert(ret == 0 && "SDL_Init failed !");
}

Game::~Game() { SDL_Quit(); }

bool Game::loadResources() {
  //批量读取文件
  _files.fbp = std::move(engine::MKFFile("fbp.mkf"));
  //   gpGlobals->f.fpFBP = UTIL_OpenRequiredFile("fbp.mkf");
  //   gpGlobals->f.fpMGO = UTIL_OpenRequiredFile("mgo.mkf");
  //   gpGlobals->f.fpBALL = UTIL_OpenRequiredFile("ball.mkf");
  //   gpGlobals->f.fpDATA = UTIL_OpenRequiredFile("data.mkf");
  //   gpGlobals->f.fpF = UTIL_OpenRequiredFile("f.mkf");
  //   gpGlobals->f.fpFIRE = UTIL_OpenRequiredFile("fire.mkf");
  //   gpGlobals->f.fpRGM = UTIL_OpenRequiredFile("rgm.mkf");
  //   gpGlobals->f.fpSSS = UTIL_OpenRequiredFile("sss.mkf");
  return true;
}

bool Game::init() {
  LOG(INFO) << "init game";
  if (!_initGameWindow()) return false;
  return true;
}

bool Game::_initGameWindow() {
  _gameWindow = new NativeWindow(1024, 768, "sdlpal editor");
  auto editor_game_window =
      _gameWindow->createImGuiWindow<editor::EditorWindow>("game-window", 320, 200, "game");
  assert(editor_game_window);
  return true;
}

int Game::run() {
  bool done = false;
  ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
  while (!done) {
    // Poll and handle events (inputs, window resize, etc.)
    // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui
    // wants to use your inputs.
    // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main
    // application, or clear/overwrite your copy of the mouse data.
    // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main
    // application, or clear/overwrite your copy of the keyboard data. Generally you may always pass
    // all inputs to dear imgui, and hide them from your application based on those two flags.

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      ImGui_ImplSDL2_ProcessEvent(&event);
      if (event.type == SDL_QUIT) done = true;
      if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE &&
          event.window.windowID == SDL_GetWindowID(_gameWindow->_window))
        done = true;
    }
    if (_gameWindow->_renderer) {
      // Start the Dear ImGui frame
      ImGui_ImplSDLRenderer_NewFrame();
      ImGui_ImplSDL2_NewFrame();
      ImGui::NewFrame();

      // render imgui windows
      _gameWindow->renderImGui();

      // Rendering
      ImGui::Render();
      _gameWindow->erase(clear_color.x * 255, clear_color.y * 255, clear_color.z * 255,
                         clear_color.z * 255);
      ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());

      _gameWindow->present();
    }
  }
  return 0;
}

}  // namespace pal