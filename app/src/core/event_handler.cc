// SPDX-License-Identifier: MIT

#include "./event_handler.hh"

#include <SDL3/SDL.h>

namespace Core {
  auto EventHandler::handle_events() -> void {
    while (SDL_PollEvent(&events)) {
      switch (events.type) {
        case SDL_EVENT_QUIT:
          is_running = false;

        default:
      }
    }
  }

  auto EventHandler::is_app_running() const -> bool { return is_running; }
} // namespace Core
