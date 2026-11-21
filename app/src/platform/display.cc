// SPDX-License-Identifier: MIT

#include "./display.hh"

#include <SDL3/SDL.h>
#include <expected>

std::expected<Platform::Display, bool>
Platform::Display::create(DisplayProperties props) {
  SDL_SetHint(SDL_HINT_ANDROID_TRAP_BACK_BUTTON, "1");
  SDL_SetHint(SDL_HINT_ORIENTATIONS, "LandscapeLeft LandscapeRight");

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                      SDL_GL_CONTEXT_PROFILE_ES);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

  if (!SDL_Init(SDL_INIT_VIDEO)) {
    return std::unexpected(false);
  }

  SDL_Window *const window =
      SDL_CreateWindow(props.title, props.width, props.height,
                       SDL_WINDOW_FULLSCREEN | SDL_WINDOW_OPENGL);

  if (!window) {
    return std::unexpected(false);
  }

  SDL_GLContext const context = SDL_GL_CreateContext(window);

  if (!context) {
    return std::unexpected(false);
  }

  SDL_GL_MakeCurrent(window, context);
  SDL_GL_SetSwapInterval(1);
  SDL_GetWindowSize(window, &props.width, &props.height);
  SDL_GetWindowSizeInPixels(window, &props.width_px_, &props.height_px_);
  props.scaling_ = SDL_GetDisplayContentScale(SDL_GetPrimaryDisplay());
  props.aspect_ratio_ = static_cast<float>(props.width) / props.height;

  return Display{
    .window_ = window,
    .context_ = context,
    .props_ = props,
  };
}

void Platform::Display::destroy() {
  SDL_GL_MakeCurrent(nullptr, nullptr);

  SDL_GL_DestroyContext(context_);
  SDL_DestroyWindow(window_);
  SDL_Quit();
}
