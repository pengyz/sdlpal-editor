#include "../framework/window.h"

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

private:
    bool _show_demo_window = true;
};