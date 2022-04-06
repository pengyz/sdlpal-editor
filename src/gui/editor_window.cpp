#include "editor_window.h"
#include "../log.h"
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
  ImGui::LabelText("aaa", "你好，中国！");
}

bool EditorWindow::init() {
  bool bOk = true;
  bOk = _initImGui();
  if (!bOk) {
    LOG(ERROR) << "initImGui failed !";
    return false;
  }
  return true;
}

bool EditorWindow::_initImGui() {
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

  // Load Fonts
  // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple
  // fonts and use ImGui::PushFont()/PopFont() to select them.
  // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the
  // font among multiple.
  // - If the file cannot be loaded, the function will return NULL. Please handle those errors in
  // your application (e.g. use an assertion, or display an error and quit).
  // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when
  // calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
  // - Read 'docs/FONTS.md' for more instructions and details.
  // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to
  // write a double backslash \\ !
  io.Fonts->AddFontDefault();
  auto font = io.Fonts->AddFontFromFileTTF("../resources/wqy-micro-hei-mono.ttf", 14, nullptr,
                                           io.Fonts->GetGlyphRangesChineseSimplifiedCommon());
  IM_ASSERT(font != nullptr);
  io.FontDefault = font;
  // io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
  // io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
  // io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
  // io.Fonts->AddFontFromFileTTF("../../misc/fonts/ProggyTiny.ttf", 10.0f);
  // ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL,
  // io.Fonts->GetGlyphRangesJapanese()); IM_ASSERT(font != NULL);

  return true;
}