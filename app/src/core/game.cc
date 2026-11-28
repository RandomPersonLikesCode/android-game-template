// SPDX-License-Identifier: MIT

#include "./game.hh"

#include "./display.hh"

#include <GLES3/gl32.h>

namespace Core {
  auto Game::create(DisplaySizeInPx display_size) -> bool {
    glViewport(0, 0, display_size.width, display_size.height);
    glClearColor(0.52f, 0.8f, 0.92f, 1.0f);

    return true;
  }

  auto Game::update(float delta) -> bool {
    glClear(GL_COLOR_BUFFER_BIT);

    return true;
  }

  auto Game::destroy() -> void {};
} // namespace Core
