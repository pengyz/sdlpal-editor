#pragma once
#include <cassert>
#include <map>
#include <string>
#include "../editor/window.h"
#include "../log.h"

struct SDL_Window;
struct SDL_Renderer;
union SDL_Event;

namespace engine {
class GameRenderer;
}

namespace editor {

/**
 * @brief Model类，imgui窗口的model数据
 *
 */
class EditorModel {
 public:
  bool _file_panel = true;  //默认显示
};

class NativeWindow : public Window {
  friend class Game;

 public:
  NativeWindow(int width, int height, const std::string& title);
  ~NativeWindow();

  template <typename T, typename... Args>
  T* createImGuiPanel(const std::string& key, Args... args) {
    assert(_imgui_panels.find(key) == _imgui_panels.end());
    T* w = new T(args...);
    if (!w->init()) {
      LOG(ERROR) << "init window failed !";
      delete w;
      return nullptr;
    }
    _imgui_panels[key] = w;
    return w;
  }

  void render() override;

  SDL_Window* window() { return _window; }

  /**
   * @brief 颜色清屏
   *
   * @param r
   * @param g
   * @param b
   */
  void erase(int r, int g, int b, int a);
  /**
   * @brief 绘制
   *
   */
  void present();

 protected:
  static int resizingEventWatcher(void* data, SDL_Event* event);
  bool init() override;
  bool _initImGui();
  void _painMainMenuBar();

 protected:
  bool _show_demo_window = true;                         // 显示demo窗口
  SDL_Window* _window = nullptr;                         // SDL窗口
  SDL_Renderer* _renderer = nullptr;                     // 渲染器
  engine::GameRenderer* _gameRender = nullptr;           // 游戏渲染器
  std::string _title;                                    // 标题
  EditorModel _model;                                    // ui model
  std::map<std::string, editor::Window*> _imgui_panels;  // imgui panels
};
}  // namespace editor
