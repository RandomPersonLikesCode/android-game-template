// SPDX-License-Identifier: MIT

#pragma once

#include <SDL3/SDL.h>
#include <utility>

namespace Core {
  enum class DisplayError {
    Ok,
    VideoInitializationError,
    WindowCreationError,
    ContextCreationError,
    DoubleInitializationError
  };

  class Display {
  public:
    ~Display() noexcept;

    [[nodiscard]]
    auto create(const char *title, int width, int height) -> DisplayError;

    // TODO: Maybe return a custom struct instead of std::pair if the
    // intent isn't clear? idk
    auto get_dimension_in_px() const -> std::pair<int, int>;
    auto get_window_ptr() const -> SDL_Window *;

  private:
    SDL_Window *window{nullptr};
    SDL_GLContext context{nullptr};
  };
} // namespace Core
