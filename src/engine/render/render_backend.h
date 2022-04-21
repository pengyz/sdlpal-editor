#pragma once

struct SDL_Texture;
struct SDL_Renderer;
struct SDL_Rect;
struct SDL_Palette;

namespace render {

class RenderBackend {
 public:
  RenderBackend(SDL_Renderer* renderer, bool bKeepAspectRatio);
  virtual ~RenderBackend();

  // 绘制函数
  virtual void Init() = 0;
  virtual void Setup() = 0;
  virtual SDL_Texture* CreateTexture(int width, int height) = 0;
  virtual void RenderCopy() = 0;

  // getter and setter
  SDL_Renderer* renderer();
  bool keepAspectRatio();
  void keepAspectRatio(bool val);
  SDL_Rect* textureRect();
  void textureRect(SDL_Rect* rect);
  int textureWidth();
  void textureWidth(int width);
  int textureHeight();
  void textureHeight(int height);
  SDL_Texture* texture();
  void texture(SDL_Texture* tex);
  SDL_Palette* palette();
  void palette(SDL_Palette* palette);

 private:
  SDL_Renderer* _renderer = nullptr;  // renderer对象
  SDL_Rect* _textureRect = nullptr;   // rect对象
  SDL_Texture* _texture = nullptr;    // 游戏纹理对象 GPU纹理
  bool _bKeepAspectRatio = true;      // 是否保持宽高比
  int _textureWidth = 320;            // texture宽度
  int _textureHeight = 200;           // texture高度
  SDL_Palette* _palette = nullptr;    // palette
};
}  // namespace render
