#pragma once
#include <fstream>
#include <map>
#include "../engine/engine.h"
#include "../engine/mkf.h"
#include "native_window.h"

namespace pal {
class NativeWindow;

/**
 * @brief 游戏类
 *
 */
class Game {
 public:
  Game();
  ~Game();
  /**
   * @brief 加载资源文件
   *
   * @return true
   * @return false
   */
  bool loadResources();
  /**
   * @brief 初始化
   *
   * @return true
   * @return false
   */
  bool init();

  /**
   * @brief 运行游戏
   *
   * @return int
   */
  int run();

 private:
  /**
   * @brief 初始化游戏窗口
   *
   * @return true
   * @return false
   */
  bool _initGameWindow();

 private:
  engine::MkfFiles _files;
  NativeWindow* _gameWindow = nullptr;
};
}  // namespace pal
