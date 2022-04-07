#pragma once
#include <string>

namespace pal {
class NativeWindow;
}

namespace editor {

class Window {
  friend class pal::NativeWindow;

 public:
  Window(int width, int height, const std::string& title)
      : _width(width), _height(height), _title(title) {}

 public:
  virtual bool init() = 0;
  virtual void render() = 0;
  bool visible() { return _visible; }
  void visible(bool visible) { _visible = visible; }

 private:
  int _width = 0;
  int _height = 0;
  bool _visible = true;
  std::string _title;
};
}  // namespace editor
