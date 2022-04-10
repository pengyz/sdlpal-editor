#include "file_panel.h"
#include <SDL.h>
#include "../log.h"
#include "imgui.h"

namespace editor {

FilePanel::FilePanel(int width, int height, const std::string& title)
    : Window(width, height, title) {}

FilePanel::~FilePanel() {}

void FilePanel::render() {
  //渲染
  ImGui::SetNextWindowSize(ImVec2(_width, _height), ImGuiCond_FirstUseEver);
  //创建背景窗口
  if (ImGui::Begin(_title.c_str(), nullptr)) {
    ImGui::LabelText("File Panel", "你好，中国！");
  }
  ImGui::End();
}

bool FilePanel::init() { return true; }

}  // namespace editor