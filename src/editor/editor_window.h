#include "window.h"

struct SDL_Renderer;

namespace editor {

class EditorWindow : public Window {
 public:
  EditorWindow(int width, int height, const std::string& title);
  ~EditorWindow();
  /**
   * @brief 渲染逻辑
   *
   */
  virtual void render() override;

  virtual bool init() override;
};
}  // namespace editor
