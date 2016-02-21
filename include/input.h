#pragma once

#include "main.h"

extern SDL_Event event;

extern bool keyboardstate[322];

int load_input ();
void input_loop();
