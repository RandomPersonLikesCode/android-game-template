// SPDX-License-Identifier: MIT

#pragma once

#include "./display.hh"

namespace Core {
  namespace Game {
    auto create(DisplaySizeInPx display_size) -> bool;
    auto update(float dt) -> bool;
    auto destroy() -> void;
  } // namespace Game
} // namespace Core
