#include <SDL_image.h>

#include "graphics.h"

// Screen resolution
const int SCREEN_SIZE[2] = {1280, 720};

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

// Window renderer
SDL_Renderer* gRenderer = NULL;

//Globally used font
TTF_Font *gFont = NULL;
TTF_Font *gFontHuge = NULL;


bool load_display()
{
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        log_error( "SDL could not initialize! SDL Error: ");
        log_error(SDL_GetError());
        success = false;
    }
    else
    {
        const char* title = "SDL Test";
        //Create window
        gWindow = SDL_CreateWindow( title,
                                    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                    SCREEN_SIZE[0], SCREEN_SIZE[1],
                                    SDL_WINDOW_SHOWN );

        if( gWindow == NULL ) {
            log_error( "Window could not be created! SDL Error: " );
            log_error(SDL_GetError());
            success = false;
        }
        else {
            //Create renderer
            gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
            if( gRenderer == NULL ) {
                log_error( "Renderer could not be created! SDL Error: " );
                log_error(SDL_GetError());
                success = false;
            }
            //Initialize renderer color
            SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
        }
    }

    return success;
}

bool load_graphics () {

    //Initialize PNG loading
    int imgFlags = IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) )
    {
        log_error( "SDL_image could not initialize! SDL_image Error: " );
        log_error(IMG_GetError());
        return false;
    }

    //Initialize SDL_ttf
    if( TTF_Init() == -1 )
    {
        log_error( "SDL_ttf could not initialize! SDL_ttf Error: " );
        log_error(TTF_GetError());
        return false;
    }

    gFont = loadFont("calibri.ttf", FONTSIZE_SMALL);
    gFontHuge = loadFont("calibri.ttf", FONTSIZE_LARGE);

    return true;
}
