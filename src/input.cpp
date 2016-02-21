#include <SDL.h>

#include "input.h"
#include "state.h"

//Event handler
SDL_Event event;

//322
bool keyboardstate[322];

int load_input () {
    // Reset keyboard state
    for (int i=0; i < 322; i++) {
        keyboardstate[i] = false;
    }

    return 1;
}

void input_loop() {
    // Iterate all events
    while( SDL_PollEvent( &event ) != 0 ){
        //User requests quit
        if( event.type == SDL_QUIT ){
            quit = true;
        }
        else if (event.type == SDL_KEYDOWN && event.key.keysym.sym <= 322){
            // Set key state as pressed
            keyboardstate[event.key.keysym.sym] = true;
        }
        else if (event.type == SDL_KEYUP && event.key.keysym.sym <= 322){
            // Set key state as released
            keyboardstate[event.key.keysym.sym] = false;
        }

        current_state->input(event);
    }
}
