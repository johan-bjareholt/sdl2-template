#pragma once

#include <SDL.h>

#include "font.h"
#include "logger.h"

// Screen resolution
extern const int SCREEN_SIZE[2];

//The window we'll be rendering to
extern SDL_Window* gWindow;

// Window renderer
extern SDL_Renderer* gRenderer;

bool load_display();

bool load_graphics ();
