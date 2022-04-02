#pragma once
#include <fstream>
#include <map>
#include "../engine/mkf/mkf.h"

namespace pal {



/**
 * @brief 游戏类
 *
 */
class Game {

 public:
  Game() = default;
  /**
   * @brief 加载资源文件
   *
   * @return true
   * @return false
   */
  bool loadResources();

 private:
  MkfFiles _files;
};
}  // namespace pal
