#pragma once

#include <SDL_ttf.h>

#include "logger.h"

const int FONTSIZE_TINY		= 15;
const int FONTSIZE_SMALL	= 25;
const int FONTSIZE_MEDIUM	= 50;
const int FONTSIZE_LARGE	= 75;
const int FONTSIZE_HUGE		= 100;

//Globally used font
extern TTF_Font *gFont;
extern TTF_Font *gFontHuge;

TTF_Font* loadFont(const char* name, const int size);
