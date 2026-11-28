// SPDX-License-Identifier: MIT

#pragma once

#include <SDL3/SDL.h>

namespace Core {
  class EventHandler {
  public:
    auto handle_events() -> void;

    auto is_app_running() const -> bool;

  private:
    SDL_Event events{};
    bool is_running{true};
  };
} // namespace Core
