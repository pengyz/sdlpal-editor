#pragma once
#include <cassert>
#include <map>
#include <string>
#include "../log.h"

struct SDL_Window;
struct SDL_Renderer;
namespace editor {
class Window;
}

namespace pal {

class NativeWindow {
  friend class Game;

 public:
  ~NativeWindow();

  template <typename T, typename... Args>
  T* createImGuiWindow(const std::string& key, Args... args) {
    assert(_imgui_windows.find(key) == _imgui_windows.end());
    T* w = new T(_renderer, args...);
    if (!w->init()) {
      LOG(ERROR) << "init window failed !";
      delete w;
      return nullptr;
    }
    _imgui_windows[key] = w;
    return w;
  }

 protected:
  /**
   * @brief 渲染所有imgui窗口
   *
   */
  void renderImGui();

 protected:
  NativeWindow(int width, int height, const std::string& title);
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
  int _width = 0;                                         // 窗口宽度
  int _height = 0;                                        // 窗口高度
  SDL_Window* _window = nullptr;                          // SDL窗口
  SDL_Renderer* _renderer = nullptr;                      // 渲染器
  std::string _title;                                     // 标题
  std::map<std::string, editor::Window*> _imgui_windows;  // imgui窗口列表
};
}  // namespace pal
