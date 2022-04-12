#include <cassert>
#include <iostream>
#include <SDL.h>
#include "engine/engine.h"
#include "game/game.h"
#include "log.h"
#include "stb_image_writer.h"

int main(int argc, char** argv) {
  engine::Engine engine(argc, argv);
  engine.setResourcePath(u8"../resources/pal/");
  bool bOk = engine.init();
  if (!bOk) {
    LOG(FATAL) << "engine init failed !";
    return -1;
  }

  pal::Game game;
  if (!game.init()) {
    LOG(ERROR) << "init game failed !";
    return -1;
  }
  //游戏逻辑开一个单独的线程执行

  SDL_Color* palette = engine.getPalette(3, false);
  auto gpPalette = SDL_AllocPalette(256);
  SDL_SetPaletteColors(gpPalette, palette, 0, 256);
  // SDL_SetSurfaceColorMod(gpScreen, 0xFF, 0xFF, 0xFF);
  uint8_t* buf = new uint8_t[320 * 200];
  engine._files.fbp.decompressChunk(buf, 320 * 200, 2);
  stbi_write_bmp("bg.bmp", 320, 200, 0, buf);
  // PAL_MKFDecompressChunk(buf, 320 * 200, MAINMENU_BACKGROUND_FBPNUM, gpGlobals->f.fpFBP);
  LOG(INFO) << "start game loop...";
#if 1
  return game.run();
#else
  return 0;
#endif
}
