#pragma once

#include <SDL.h>

#include "sprite.h"

class State;

extern State *current_state;

/*
    Base state class
*/

class State {
    public:
        State () {};
        virtual void update () {};
        virtual void blit() {
        	aliveSprites.blit();
        };
        virtual void input (SDL_Event) {};
};
