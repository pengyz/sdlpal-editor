#pragma once
#include <SDL.h>
#include <string>

class Window {
  friend class Application;

 public:
  ~Window();
  virtual bool init() { return false; }

 protected:
  virtual void render() = 0;
 protected:
  Window(int width, int height, const std::string& title);

 protected:
  SDL_Window* _window = nullptr;
  SDL_Renderer* _renderer = nullptr;
  std::string _title;
};