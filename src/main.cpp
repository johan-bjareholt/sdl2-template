#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL.h"

// Load self header
#include "main.h"

// Quit flag
bool quit = false;
// Initialize current state pointer
State* current_state = NULL;

void close();



int main( int argc, char* args[] )
{
    log_init(DEBUG);
	// Load up window
    log_debug("Loading display");
	if ( !load_display() ){
        log_debug("Failed to initialize display");
        return -1;
	}

    // Loading graphics
    if ( !load_graphics() ){
        log_debug("Failed to initialize graphics");
    }

    // Check for gamecontroller
    find_controllers();

    // Load input
    if ( !load_input() ){
        log_debug("Failed to initialize input");
        return -1;
    }

    // Load states
    mainMenu = new Menu();
    current_state = mainMenu;
    // set state

	// Game loop
    log_debug("Entering loop");
    timer.start();
	while( !quit )
    {
    	// Check inputs
        input_loop();
        // Game logic
        current_state->update();
		//Clear screen
        SDL_RenderClear( gRenderer );
        //Blit sprites
        current_state->blit();
        //Update screen
        SDL_RenderPresent( gRenderer );
        // Tick timer
        timer.tick();
    }

	//Free resources and close SDL
	close();

	return 0;
}

void close()
{
	// Clear all sprites
    aliveSprites.clear();
    //Destroy window
	SDL_DestroyRenderer( gRenderer );
	gWindow = NULL;
	//Destroy renderer
    SDL_DestroyWindow( gWindow );
    gRenderer = NULL;

	//Quit SDL subsystems
    TTF_Quit();
	SDL_Quit();
}
