#pragma once
#include "SDL.h"
#include <array>

namespace render {
class RenderBackend;
}

namespace engine {

using PaletteColors = std::array<SDL_Color, 256>;


/**
 * @brief 渲染器
 *
 */
class GameRenderer {
 public:
  GameRenderer(SDL_Renderer* renderer);
  ~GameRenderer();
  /**
   * @brief 初始化
   *
   * @param widht
   * @param height
   * @return true
   * @return false
   */
  bool init(int widht, int height);

  /**
   * @brief 获取texuture
   *
   * @return SDL_Texture*
   */
  SDL_Texture* texture();

  /**
   * @brief 颜色填充
   *
   * @param color
   * @param rect
   */
  void fillRect(SDL_Colour color, const SDL_Rect& rect);

    /**
   * @brief Get the specified palette in pat.mkf file.
   *
   * @param iPaletteNum number of the palette.
   * @param fNight whether use the night palette or not.
   * @return SDL_Color* Pointer to the palette. NULL if failed.
   */
  SDL_Color* getPalette(int32_t iPaletteNum, bool fNight);
  /**
   * @brief Set the palette of the screen.
   * 
   * @param rgPalette array of 256 colors.
   */
  void setPalette(SDL_Color rgPalette[256]);

 private:
  PaletteColors _paletteColors;
  SDL_Surface* _logicScreen;
  SDL_Palette* _palette;
  render::RenderBackend* _backend = nullptr;  // backend
  SDL_Renderer* _renderer = nullptr;          // renderer
};
}  // namespace engine