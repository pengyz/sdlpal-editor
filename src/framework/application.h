#pragma
#include <string>
#include <vector>

class Window;

class Application {
 public:
  Application();
  ~Application();
  /**
   * @brief 创建窗口
   *
   * @return Window*
   */
  template<typename T, typename... Args>
  Window* createWindow(Args... arg) {
    auto w = new T(arg...);
    _windows.push_back(w);
    return w;
  }
  
  /**
   * @brief 执行消息循环
   *
   * @return int
   */
  int runLoop();

 private:
  std::vector<Window*> _windows;  //所有已创建的窗口
};