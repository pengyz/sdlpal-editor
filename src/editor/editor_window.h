#include "window.h"

struct SDL_Renderer;

namespace editor {

class EditorWindow : public Window {
 public:
  EditorWindow(SDL_Renderer* renderer, int width, int height, const std::string& title);
  ~EditorWindow();
  /**
   * @brief 渲染逻辑
   *
   */
  virtual void render() override;

  virtual bool init() override;

 protected:
  /**
   * @brief 初始化imgui
   *
   * @return true
   * @return false
   */
  bool _initImGui();

 private:
  SDL_Renderer* _renderer = nullptr;
  bool _show_demo_window = true;
};
}  // namespace editor
