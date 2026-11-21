// SPDX-License-Identifier: MIT

#include "../core/game.hh"
#include "./display.hh"
#include "./event_handler.hh"

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <expected>

int main(int argc, char **argv) {
  std::expected<Platform::Display, bool> dp =
      Platform::Display::create(Platform::DisplayProperties{
        .title = "Game Template",
        .width = 800,
        .height = 600,
      });

  if (!dp.has_value()) {
    return false;
  }

  if (!Core::Game::create(dp->props_.width_px_, dp->props_.height_px_)) {
    Core::Game::destroy();
    dp->destroy();
    return 1;
  }

  Platform::EventHandler event_handler = {};

  while (event_handler.is_running) {
    while (SDL_PollEvent(&event_handler.events)) {
      event_handler.handle_events();
    }

    if (!Core::Game::update()) {
      event_handler.is_running = false;
      return 1;
    }

    SDL_GL_SwapWindow(dp->window_);
  }

  Core::Game::destroy();
  dp->destroy();
  return 0;
}
