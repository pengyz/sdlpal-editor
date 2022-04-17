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
    ImGui::Image((ImTextureID)_renderer->texture(), ImVec2(320.0, 200.0));
  }
  ImGui::End();
}

bool GamePanel::init() {
  _renderer->fillRect(SDL_Colour(255, 0, 0, 0), {0, 0, 100, 100});
  return true;
}

}  // namespace editor