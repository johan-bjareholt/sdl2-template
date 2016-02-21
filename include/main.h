#pragma once

#define PLATFORM_UNSPECIFIED 0
#define PLATFORM_WINDOWS 1
#define PLATFORM_LINUX   2
#define PLATFORM_ANDROID 3

#ifdef __ANDROID__
    const int platform = PLATFORM_ANDROID;
#elif WIN32
    const int platform = PLATFORM_WINDOWS;
#elif __unix__
    const int platform = PLATFORM_LINUX;
#else
    const int platform = PLATFORM_UNSPECIFIED;
#endif

// Load logger
#include "logger.h"

// Load baseclasses
#include "timer.h"
#include "graphics.h"
#include "gamecontroller.h"
#include "input.h"

// Load states
#include "state.h"
#include "states/menu.h"


extern bool quit;
