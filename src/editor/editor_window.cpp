#include "editor_window.h"
#include <SDL.h>
#include "../log.h"
#include "imgui.h"

namespace editor {

EditorWindow::EditorWindow(int width, int height, const std::string& title)
    : Window(width, height, title) {}

EditorWindow::~EditorWindow() {}

void EditorWindow::render() {
  //渲染
  ImGui::SetNextWindowSize(ImVec2(_width, _height), ImGuiCond_FirstUseEver);
  //创建背景窗口
  if (ImGui::Begin("editor_window", &_visible)) {
    ImGui::LabelText("Editor Window", "你好，中国！");
  }
  ImGui::End();
}

bool EditorWindow::init() { return true; }

}  // namespace editor