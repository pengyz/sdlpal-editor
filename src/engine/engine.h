#pragma once
#include <filesystem>
#include "mkf.h"

namespace engine {

struct MkfFiles {
  engine::MKFFile fbp;
  engine::MKFFile mgo;
  engine::MKFFile ball;
  engine::MKFFile data;
  engine::MKFFile f;
  engine::MKFFile fire;
  engine::MKFFile rgm;
  engine::MKFFile sss;
};

/**
 * @brief 引擎抽象类
 *
 */
class Engine {
 public:
  Engine(int argc, char** argv);
  ~Engine();
  static bool isWin95();
  /**
   * @brief 设置资源路径
   *
   * @param path
   */
  void setResourcePath(const std::filesystem::path& path);

  /**
   * @brief 初始化
   *
   * @return true
   * @return false
   */
  bool init();

 private:
  /**
   * @brief 加载文件
   *
   * @param path
   * @param file
   * @return true
   * @return false
   */
  bool loadMKFFile(const std::filesystem::path& path, MKFFile& file);

  /**
   * @brief 初始化log
   *
   * @return true
   * @return false
   */
  bool _initLog();

  /**
   * @brief 加载资源
   *
   * @return true
   * @return false
   */
  bool _loadResources();

 private:
  static bool _isWIn95;

  int _argc = 0;
  char** _argv = nullptr;
  std::filesystem::path _resourcePath;

  MkfFiles _files;
};
}  // namespace engine