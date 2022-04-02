#include <iostream>
#include "framework/application.h"
#include "mkf/mkf.h"
#include "gui/editor_window.h"

int main(int argc, char** argv) {
  Application app;
  auto w = app.createWindow<EditorWindow>(1024, 768, "sdlpal editor");
  w->init();
  //加载文件
  MKFFile mpkMap(MKFFile::DecompressType::yj1);
  if (!mpkMap.open("/home/peng/workspace/sdlpal/build/map.mkf")) {
    printf("open file map.mkf failed !\n");
    return -1;
  }
  MKFFile mpkGop(MKFFile::DecompressType::yj1);
  if (!mpkGop.open("/home/peng/workspace/sdlpal/build/gop.mkf")) {
    printf("open file gop.mkf failed !\n");
    return -1;
  }

  return app.runLoop();

}
