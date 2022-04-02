#include <cassert>
#include <iostream>
#include "engine/engine.h"
#include "framework/application.h"
#include "gui/editor_window.h"
#include "log.h"

int main(int argc, char** argv) {
  engine::Engine engine(argc, argv);
  engine.setResourcePath(u8"/home/peng/workspace/sdlpal/build");

  Application app;
  auto w = app.createWindow<EditorWindow>(1024, 768, "sdlpal editor");
  w->init();
  bool bOk = engine.init();
  if(!bOk) {
    LOG(FATAL) << "engine init failed !";
    return -1;
  }
  LOG(INFO) << "start app loop...";
  return app.runLoop();
}
