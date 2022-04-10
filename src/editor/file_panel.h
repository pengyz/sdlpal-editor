#include "window.h"

struct SDL_Renderer;

namespace editor {

class FilePanel : public Window {
 public:
  FilePanel(int width, int height, const std::string& title);
  ~FilePanel();
  /**
   * @brief 渲染逻辑
   *
   */
  virtual void render() override;

  virtual bool init() override;
};
}  // namespace editor
