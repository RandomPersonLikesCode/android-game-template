project("main")

add_library("main" SHARED
  # Main
  "platform/main.cc"
  "core/display.cc"
  "core/game.cc"
  "core/event_handler.cc"

  "core/display.hh"
  "core/game.hh"
  "core/event_handler.hh"

  # Third-party
)

set_target_properties("main" PROPERTIES
  CXX_VISIBILITY_PRESET hidden
  VISIBILITY_INLINES_HIDDEN TRUE
)

target_compile_options("main" PRIVATE
  "-Wall"
  "-Wextra"
  "-Wpedantic"
  "-fno-rtti"
  "-fno-exceptions"
)

target_compile_definitions("main" PRIVATE
  $<$<CONFIG:Debug>:SDL_ASSERT_LEVEL=3>
  $<$<CONFIG:Release>:SDL_ASSERT_LEVEL=0>
)

target_include_directories("main" PRIVATE
  "${CMAKE_SOURCE_DIR}/third_party/include"
)

target_link_libraries("main" PRIVATE
  "${android}"
  "${egl}"
  "${gles}"
  "${log}"

  SDL3::SDL3
)
