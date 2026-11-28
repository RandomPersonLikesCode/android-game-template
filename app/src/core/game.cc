// SPDX-License-Identifier: MIT

#include "./game.hh"

#include <GLES3/gl32.h>
#include <utility>

namespace Core {
  auto Game::create(std::pair<int, int> window_size) -> bool {
    glViewport(0, 0, window_size.first, window_size.second);
    glClearColor(0.52f, 0.8f, 0.92f, 1.0f);

    return true;
  }

  auto Game::update(float dt) -> bool {
    glClear(GL_COLOR_BUFFER_BIT);

    return true;
  }

  auto Game::destroy() -> void {};
} // namespace Core
