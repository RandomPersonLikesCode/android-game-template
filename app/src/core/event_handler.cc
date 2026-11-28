// SPDX-License-Identifier: MIT

#include "./event_handler.hh"

#include <SDL3/SDL.h>

namespace Core {
  auto EventHandler::handle_events() -> void {
    switch (events.type) {
      case SDL_EVENT_QUIT:
        is_running = false;
    }
  }
} // namespace Core
