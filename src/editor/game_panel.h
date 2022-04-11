#pragma once

#include "window.h"

struct SDL_Texture;

namespace editor {

class GamePanel : public Window {
 public:
  GamePanel(int width, int height, const std::string& title);
  ~GamePanel();
  /**
   * @brief 渲染逻辑
   *
   */
  virtual void render() override;

  virtual bool init() override;
private:
  SDL_Texture* _texture;
};
}  // namespace editor
