#include "game.h"

namespace pal {
bool Game::loadResources() {
  //批量读取文件
  _files.fbp = std::move(engine::MKFFile("fbp.mkf"));
//   gpGlobals->f.fpFBP = UTIL_OpenRequiredFile("fbp.mkf");
//   gpGlobals->f.fpMGO = UTIL_OpenRequiredFile("mgo.mkf");
//   gpGlobals->f.fpBALL = UTIL_OpenRequiredFile("ball.mkf");
//   gpGlobals->f.fpDATA = UTIL_OpenRequiredFile("data.mkf");
//   gpGlobals->f.fpF = UTIL_OpenRequiredFile("f.mkf");
//   gpGlobals->f.fpFIRE = UTIL_OpenRequiredFile("fire.mkf");
//   gpGlobals->f.fpRGM = UTIL_OpenRequiredFile("rgm.mkf");
//   gpGlobals->f.fpSSS = UTIL_OpenRequiredFile("sss.mkf");
  return true;
}

}  // namespace pal