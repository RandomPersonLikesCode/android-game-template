// SPDX-License-Identifier: MIT

#include "./display.hh"

#include <SDL3/SDL.h>
#include <utility>

namespace Core {
  Display::~Display() noexcept {
    SDL_GL_MakeCurrent(nullptr, nullptr);
    SDL_GL_DestroyContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
  }

  [[nodiscard]]
  auto Display::create(const char *title, int width, int height)
      -> DisplayError {
    // Just to avoid double initialization when .create is called twice
    // or more
    if (window != nullptr || context != nullptr) {
      return DisplayError::DoubleInitializationError;
    }

    SDL_SetHint(SDL_HINT_ANDROID_TRAP_BACK_BUTTON, "1");
    SDL_SetHint(SDL_HINT_ORIENTATIONS, "LandscapeLeft LandscapeRight");

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                        SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    if (!SDL_Init(SDL_INIT_VIDEO)) {
      return DisplayError::VideoInitializationError;
    }

    window = SDL_CreateWindow(title, width, height,
                              SDL_WINDOW_FULLSCREEN | SDL_WINDOW_OPENGL);

    if (!window) {
      return DisplayError::WindowCreationError;
    }

    context = SDL_GL_CreateContext(window);

    if (!context) {
      return DisplayError::ContextCreationError;
    }

    SDL_GL_MakeCurrent(window, context);
    SDL_GL_SetSwapInterval(1); // VSync

    return DisplayError::Ok;
  }

  auto Display::get_dimension_in_px() const -> std::pair<int, int> {
    int width{};
    int height{};

    SDL_GetWindowSizeInPixels(window, &width, &height);

    return {width, height};
  }

  auto Display::get_window_ptr() const -> SDL_Window * { return window; }
} // namespace Core
