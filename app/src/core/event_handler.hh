// SPDX-License-Identifier: MIT

#pragma once

#include <SDL3/SDL.h>

namespace Core {
  struct EventHandler {
    SDL_Event events{};
    bool is_running{true};

    auto handle_events() -> void;
  };
} // namespace Core
