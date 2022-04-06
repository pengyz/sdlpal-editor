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

protected:
    /**
     * @brief 初始化imgui
     * 
     * @return true 
     * @return false 
     */
    bool _initImGui();

private:
    bool _show_demo_window = true;
};