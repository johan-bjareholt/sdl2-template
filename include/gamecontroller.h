#pragma once

#include "SDL.h"

#include "logger.h"

extern bool controller_enabled;
extern SDL_GameController* controller;

bool load_controller (int i);

void find_controllers ();
