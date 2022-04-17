#pragma once

#include "window.h"

namespace engine {
  class GameRenderer;
}

namespace editor {

class GamePanel : public Window {
 public:
  GamePanel(engine::GameRenderer* renderer, int width, int height, const std::string& title);
  ~GamePanel();
  /**
   * @brief 渲染逻辑
   *
   */
  virtual void render() override;

  virtual bool init() override;
private:
  engine::GameRenderer* _renderer = nullptr;
};
}  // namespace editor
