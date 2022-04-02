#include "engine.h"
#include "../log.h"

namespace engine {
bool Engine::_isWIn95 = false;

Engine::Engine(int argc, char** argv) : _argc(argc), _argv(argv) {
  _resourcePath = std::filesystem::current_path();
}

Engine::~Engine() { ShutdownGoogleLogging(); }

bool Engine::isWin95() { return _isWIn95; }

void Engine::setResourcePath(const std::filesystem::path& path) { _resourcePath = path; }

bool Engine::init() {
  if (!_initLog()) return false;
  if (!_loadResources()) return false;
  return true;
}

bool Engine::loadMKFFile(const std::filesystem::path& path, MKFFile& file) {
  if (!path.is_absolute()) {
    file = MKFFile(_resourcePath / path);
  } else {
    file = MKFFile(path);
  }
  return file;
}

bool Engine::_initLog() {
#if 0
  auto log_path = std::filesystem::u8path(_argv[0]).remove_filename() / "logs";
  std::error_code ec;
  if (!std::filesystem::exists(log_path, ec)) {
    if (!std::filesystem::create_directories(log_path, ec)) {
      return false;
    }
  }
    // 设置日志路径
  FLAGS_log_dir = log_path.string();
#else
  FLAGS_logtostdout = true;       //输出到stderr而不是文件
  FLAGS_colorlogtostdout = true;  //彩色输出
#endif

  InitGoogleLogging(_argv[0]);

  return true;
}

bool Engine::_loadResources() {
  //加载mkf资源文件
  if (!loadMKFFile("fbp.mkf", _files.fbp)) {
    LOG(ERROR) << "open fbp.mkf failed !";
    return false;
  }
  if (!loadMKFFile("mgo.mkf", _files.mgo)) {
    LOG(ERROR) << "open mgo.mkf failed !";
    return false;
  }
  if (!loadMKFFile("ball.mkf", _files.ball)) {
    LOG(ERROR) << "open ball.mkf failed !";
    return false;
  }
  if (!loadMKFFile("data.mkf", _files.data)) {
    LOG(ERROR) << "open data.mkf failed !";
    return false;
  }
  if (!loadMKFFile("f.mkf", _files.f)) {
    LOG(ERROR) << "open f.mkf failed !";
    return false;
  }
  if (!loadMKFFile("fire.mkf", _files.fire)) {
    LOG(ERROR) << "open fire.mkf failed !";
    return false;
  }
  if (!loadMKFFile("rgm.mkf", _files.rgm)) {
    LOG(ERROR) << "open rgm.mkf failed !";
    return false;
  }
  if (!loadMKFFile("sss.mkf", _files.sss)) {
    LOG(ERROR) << "open sss.mkf failed !";
    return false;
  }

  return true;
}

}  // namespace engine