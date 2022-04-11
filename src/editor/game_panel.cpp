#include "game_panel.h"
#include <SDL.h>
#include "../log.h"
#include "imgui.h"

namespace editor {

GamePanel::GamePanel(int width, int height, const std::string& title)
    : Window(width, height, title) {}

GamePanel::~GamePanel() {}

void GamePanel::render() {
  //渲染
  ImGui::SetNextWindowSize(ImVec2(_width, _height), ImGuiCond_FirstUseEver);
  //创建背景窗口
  if (ImGui::Begin(_title.c_str(), nullptr)) {
      // ImGui::Image()
  }
  ImGui::End();
}

bool GamePanel::init() {
  return true; 
}

}  // namespace editor