// SPDX-License-Identifier: MIT

#pragma once

#include "./display.hh"

namespace Core::Game {
  auto create(DisplaySizeInPx display_size) -> bool;
  auto update(float delta) -> bool;
  auto destroy() -> void;
} // namespace Core::Game
