#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

#include "graphics.h"

#define ALIGN_LEFT 0
#define ALIGN_RIGHT 1
#define ALIGN_TOP 2
#define ALIGN_BOTTOM 3
#define ALIGN_CENTER 4

class Image {
    public:
        SDL_Texture* texture;
        SDL_Surface* surface;
        // Source rect
        SDL_Rect rect;

        Image(int,int);
        ~Image();
        bool blit(SDL_Rect*);
        // Convert software surface to hardware texture
        bool update();
        // Load image from resource
        bool loadImage(const char*);
        bool loadText( const char*, TTF_Font*, SDL_Color, SDL_Color, int=ALIGN_CENTER );
        // Apply surface layer ontop
        bool blitOn( SDL_Surface*, int=0, int=0 );
        // Not working
        bool rotate(double);
        // Fill whole image with a specific color
        void fill(int,int,int);
        // Clear image
        void clear();
};
