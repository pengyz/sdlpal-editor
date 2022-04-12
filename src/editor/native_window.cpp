#include "native_window.h"
#include <cassert>
#include "../editor/file_panel.h"
#include "../editor/window.h"
#include "../log.h"
#include "SDL.h"
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_sdlrenderer.h"

namespace editor {

NativeWindow::NativeWindow(int width, int height, const std::string& title)
    : Window(width, height, title) {
  _window = SDL_CreateWindow(_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _width,
                             _height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
  assert(_window && "create window failed !");
  _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
  assert(_renderer && "create renderer failed !");
  bool bOk = init();
  assert(bOk);
  SDL_AddEventWatch(&NativeWindow::resizingEventWatcher, this);
}

bool NativeWindow::init() {
  bool bOk = true;
  bOk = _initImGui();
  if (!bOk) {
    LOG(ERROR) << "initImGui failed !";
    return false;
  }
  //创建窗口
  createImGuiPanel<FilePanel>("FilePanel", 800, 600, "文件");
  return true;
}

void NativeWindow::render() {
  //主窗口菜单项
  _painMainMenuBar();

  //渲染
  if (_show_demo_window) {
    ImGui::ShowDemoWindow(&_show_demo_window);
  }
  //创建dock space
  ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

  for (auto w : _imgui_panels) {
    if (w.second->visible()) w.second->render();
  }
}

void NativeWindow::_painMainMenuBar() {
  if (ImGui::BeginMainMenuBar()) {
    if (ImGui::BeginMenu("File")) {
      if (ImGui::MenuItem("Open File", "Alt + o", nullptr)) {
        LOG(INFO) << "Open File clicked !";
      }
      if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip("Open a new file");
      }
      ImGui::EndMenu();
    }
    if(ImGui::BeginMenu("Layout")) {
      if(ImGui::MenuItem("Reset", "Alt + r", nullptr)) {
        LOG(INFO) << "Reset all panels !";
      }
      if(ImGui::IsItemHovered()) {
        ImGui::SetTooltip("Reset all editor panels");
      }
      if(ImGui::MenuItem("File Panel", "Alt + f", &_model._file_panel)) {
        LOG(INFO) << "Reset all panels !";
        if(_model._file_panel && !_imgui_panels["FilePanel"]->visible()) {
          _imgui_panels["FilePanel"]->visible(true);
        } else if(!_model._file_panel && _imgui_panels["FilePanel"]->visible()) {
          _imgui_panels["FilePanel"]->visible(false);
        }
      }
      if(ImGui::IsItemHovered()) {
        ImGui::SetTooltip("Reset all editor panels");
      }
      ImGui::EndMenu();
    }
    
    ImGui::EndMainMenuBar();
  }
}

bool NativeWindow::_initImGui() {
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  // Setup SDL_Renderer instance
  SDL_RendererInfo info;
  SDL_GetRendererInfo(_renderer, &info);
  SDL_Log("Current SDL_Renderer: %s", info.name);

  // Setup Dear ImGui context
  ImGuiIO& io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
  io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
  io.IniFilename = "gui.ini";
  // io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
  // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

  // Setup Dear ImGui style
  ImGui::StyleColorsDark();
  // ImGui::StyleColorsClassic();

  // Setup Platform/Renderer backends
  ImGui_ImplSDL2_InitForSDLRenderer(SDL_RenderGetWindow(_renderer), _renderer);
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
  auto font = io.Fonts->AddFontFromFileTTF("./resources/wqy-micro-hei-mono.ttf", 14, nullptr,
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

NativeWindow::~NativeWindow() {
  for (const auto& pair : _imgui_panels) {
    delete pair.second;
  }
  _imgui_panels.clear();
  ImGui::DestroyContext();

  ImGui_ImplSDLRenderer_Shutdown();
  ImGui_ImplSDL2_Shutdown();

  SDL_DestroyWindow(_window);
  _window = nullptr;
}

int NativeWindow::resizingEventWatcher(void* data, SDL_Event* event) {
  auto window = static_cast<NativeWindow*>(data);
  if (event->type == SDL_WINDOWEVENT && event->window.event == SDL_WINDOWEVENT_RESIZED) {
    SDL_Window* win = SDL_GetWindowFromID(event->window.windowID);
    if (win == window->_window) {
      window->_width = event->window.data1;
      window->_height = event->window.data2;
    }
  }
  return 0;
}

void NativeWindow::present() { SDL_RenderPresent(_renderer); }

void NativeWindow::erase(int r, int g, int b, int a) {
  SDL_SetRenderDrawColor(_renderer, (Uint8)r, (Uint8)g, (Uint8)b, (Uint8)a);
  SDL_RenderClear(_renderer);
}

}  // namespace editor
