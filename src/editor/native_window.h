#pragma once
#include <cassert>
#include <map>
#include <string>
#include "../editor/window.h"
#include "../log.h"

struct SDL_Window;
struct SDL_Renderer;
union SDL_Event;

namespace editor {

class NativeWindow : public Window {
  friend class Game;

 public:
  NativeWindow(int width, int height, const std::string& title);
  ~NativeWindow();

  template <typename T, typename... Args>
  T* createImGuiWindow(const std::string& key, Args... args) {
    assert(_imgui_windows.find(key) == _imgui_windows.end());
    T* w = new T(args...);
    if (!w->init()) {
      LOG(ERROR) << "init window failed !";
      delete w;
      return nullptr;
    }
    _imgui_windows[key] = w;
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

 protected:
  bool _show_demo_window = true;      // 显示demo窗口
  SDL_Window* _window = nullptr;      // SDL窗口
  SDL_Renderer* _renderer = nullptr;  // 渲染器
  std::string _title;                 // 标题
  // editor::MainWindow* _editorWindow;  // 编辑器imgui窗口
  std::map<std::string, editor::Window*> _imgui_windows;  // imgui窗口列表
};
}  // namespace editor
