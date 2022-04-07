#include <cassert>
#include <iostream>
#include "engine/engine.h"
#include "game/game.h"
#include "log.h"

int main(int argc, char** argv) {
  engine::Engine engine(argc, argv);
  bool bOk = engine.init();
  if (!bOk) {
    LOG(FATAL) << "engine init failed !";
    return -1;
  }
  engine.setResourcePath(u8"/home/peng/workspace/sdlpal/build");

  pal::Game game;
  if (!game.init()) {
    LOG(ERROR) << "init game failed !";
    return -1;
  }
  //游戏逻辑开一个单独的线程执行

  LOG(INFO) << "start app loop...";
  return game.run();
}
