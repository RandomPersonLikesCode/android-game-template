// SPDX-License-Identifier: MIT

#pragma once

#include <SDL3/SDL.h>

namespace Core {
  enum class DisplayError {
    Ok,
    VideoInitializationError,
    WindowCreationError,
    ContextCreationError,
    DoubleInitializationError
  };

  struct DisplaySizeInPx {
    int width{0};
    int height{0};
  };

  class Display {
  public:
    ~Display() noexcept;

    [[nodiscard]]
    auto create(const char *title, int width, int height) -> DisplayError;

    auto get_size_in_px() const -> DisplaySizeInPx;
    auto get_window_ptr() const -> SDL_Window *;

  private:
    SDL_Window *window{nullptr};
    SDL_GLContext context{nullptr};
  };
} // namespace Core
