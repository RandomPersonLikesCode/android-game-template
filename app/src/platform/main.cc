// SPDX-License-Identifier: MIT

#include "../core/display.hh"
#include "../core/event_handler.hh"
#include "../core/game.hh"

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

auto main(int argc, char **argv) -> int {
  Core::Display primary_display{};

  if (auto error = primary_display.create("Game Template", 800, 500);
      error != Core::DisplayError::Ok) {
    SDL_Log("Display error: %d", static_cast<int>(error));
  }

  if (!Core::Game::create(primary_display.get_dimension_in_px())) {
    Core::Game::destroy();
    return 1;
  }

  Core::EventHandler event_handler = {};

  while (event_handler.is_running) {
    while (SDL_PollEvent(&event_handler.events)) {
      event_handler.handle_events();
    }

    if (!Core::Game::update(0.0f)) {
      event_handler.is_running = false;
      return 1;
    }

    SDL_GL_SwapWindow(primary_display.get_window_ptr());
  }

  Core::Game::destroy();
  return 0;
}
