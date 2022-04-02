#include "editor_window.h"
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_sdlrenderer.h"

EditorWindow::EditorWindow(int width, int height, const std::string& title)
    : Window(width, height, title) {}

EditorWindow::~EditorWindow() {
  ImGui_ImplSDLRenderer_Shutdown();
  ImGui_ImplSDL2_Shutdown();
  ImGui::DestroyContext();

  SDL_DestroyRenderer(_renderer);
  _renderer = nullptr;
}

void EditorWindow::render() {
  //渲染
  if (_show_demo_window) {
    ImGui::ShowDemoWindow(&_show_demo_window);
  }
}

bool EditorWindow::init() {
  // Setup SDL_Renderer instance
  _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
  if (_renderer == NULL) {
    SDL_Log("Error creating SDL_Renderer!");
    return false;
  }
  SDL_RendererInfo info;
  SDL_GetRendererInfo(_renderer, &info);
  SDL_Log("Current SDL_Renderer: %s", info.name);

  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO();
  (void)io;
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
  // io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
  // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

  // Setup Dear ImGui style
  ImGui::StyleColorsDark();
  // ImGui::StyleColorsClassic();

  // Setup Platform/Renderer backends
  ImGui_ImplSDL2_InitForSDLRenderer(_window, _renderer);
  ImGui_ImplSDLRenderer_Init(_renderer);
  return true;
}