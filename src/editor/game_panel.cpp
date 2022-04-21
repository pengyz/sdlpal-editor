#include "game_panel.h"
#include <SDL.h>
#include "../engine/game_renderer.h"
#include "../log.h"
#include "imgui.h"

namespace editor {

GamePanel::GamePanel(engine::GameRenderer* renderer, int width, int height,
                     const std::string& title)
    : Window(width, height, title), _renderer(renderer) {}

GamePanel::~GamePanel() {}

void GamePanel::render() {
  //渲染
  ImGui::SetNextWindowSize(ImVec2(_width, _height), ImGuiCond_FirstUseEver);
  //创建背景窗口
  if (ImGui::Begin(_title.c_str(), nullptr)) {
    int w = 0, h = 0;
    SDL_QueryTexture(_renderer->texture(), nullptr, nullptr, &w, &h);
    ImGui::Image((ImTextureID)_renderer->texture(), {(float)w * 2.0f, (float)h * 2.0f});
  }
  ImGui::End();
}

bool GamePanel::init() {
  for (int i = 0; i < 10; i++) {
    _renderer->fillRect({Uint8(100 + 15 * i), Uint8(55 + 20 * i), Uint8(10 + 17 * i), 0}, {0, 0, 100 - 10 * i, 100 - 10 * i});
  }
  return true;
}

}  // namespace editor