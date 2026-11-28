// SPDX-License-Identifier: MIT

#pragma once

#include <utility>

namespace Core {
  namespace Game {
    auto create(std::pair<int, int> window_size) -> bool;
    auto update(float dt) -> bool;
    auto destroy() -> void;
  } // namespace Game
} // namespace Core
