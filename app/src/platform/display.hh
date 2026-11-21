// SPDX-License-Identifier: MIT

#pragma once

#include <SDL3/SDL.h>
#include <expected>

namespace Platform {
  struct DisplayProperties {
    char const *title = "Untitled";
    int width = 800;
    int height = 600;

    int width_px_ = 0;
    int height_px_ = 0;
    float aspect_ratio_ = 0.0f;
    float scaling_ = 1.0f;
  };

  struct Display {
    SDL_Window *window_ = nullptr;
    SDL_GLContext context_ = nullptr;
    DisplayProperties props_ = {};

    // TODO: replace the Error type for something more descriptive
    static std::expected<Display, bool> create(DisplayProperties props);
    void destroy();
  };
} // namespace Platform
