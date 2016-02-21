#include <SDL_image.h>
#include <SDL_ttf.h>

#include "image.h"

/*
    Image class section
*/

Image::Image (int w, int h) {
    this->surface = SDL_CreateRGBSurface(0, // Surface flags
                              w, h, 32, // width, height, depth
                              0, 0, 0, 255); // RGBA mask
    if(this->surface == NULL) {
        fprintf(stderr, "CreateRGBSurface failed: %s\n", SDL_GetError());
        exit(1);
    }
    // Initializes source rect
    this->rect = {0,0,w,h};
}

Image::~Image () {
    this->clear();
}

bool Image::blit(SDL_Rect* dstrect){
    //Render texture to screen
    SDL_RenderCopy( gRenderer, this->texture, &rect, dstrect );
    return true;
}

bool Image::update(){
    /*
        Applies surface to hardware texture
    */
    SDL_DestroyTexture( this->texture );
    this->texture = NULL;

    this->texture = SDL_CreateTextureFromSurface( gRenderer, this->surface);
    if( this->texture == NULL )
    {
        log_error( "Unable to create texture! SDL Error:" );
        log_error(SDL_GetError());
        return false;
    }

    this->rect.w = this->surface->w;
    this->rect.h = this->surface->h;

    return true;
}

bool Image::loadImage( const char* path )
{
    //Load image at specified path
    this->surface = IMG_Load( path );
    if( this->surface == NULL )
    {
        log_error( "Unable to load image %s! SDL Error: %s\n");
        log_error(path);
        log_error(SDL_GetError());
        return false;
    }

    // Apply surface to texture
    this->update();

    return true;
}

bool Image::loadText( const char* text, TTF_Font* font, SDL_Color textColor, SDL_Color bgColor, int align )
{
    //Render text surface
    SDL_Surface* fontSurface;
    /*if ( bgColor == NULL){
        fontSurface = TTF_RenderText_Solid( font, text, textColor );
    }*/
    //else {
        fontSurface = TTF_RenderText_Shaded( font, text, textColor, bgColor );
    //}
    if( fontSurface == NULL )
    {
        log_error( "Unable to render text surface! SDL_ttf Error:");
        log_error(TTF_GetError());
        return false;
    }

    int x_offset = 0;
    int y_offset = 0;
    switch (align)
    {
        case ALIGN_CENTER:
            x_offset = (this->surface->w/2)-(fontSurface->w/2);
            y_offset = (this->surface->h/2)-(TTF_FontHeight(font)/2);
            break;
        default:
            break;
    }

    this->blitOn(fontSurface, x_offset, y_offset );

    // Apply surface to texture
    this->update();

    return true;
}

bool Image::blitOn ( SDL_Surface* over_surface, int x, int y ) {

    SDL_Rect over_rect_src = {0,0, over_surface->w, over_surface->h};
    SDL_Rect over_rect_dst = {x,y, over_surface->w, over_surface->h};

    int result = SDL_BlitSurface(over_surface, &over_rect_src, surface, &over_rect_dst);
    if (result < 0) {
        log_error("Couldn't blit surface ontop of another: %s\n");
        log_error(SDL_GetError());
        return false;
    }
    return true;
}

bool Image::rotate ( double angle ){
    if ( !SDL_RenderCopyEx(gRenderer,this->texture,NULL,NULL,angle,NULL,SDL_FLIP_NONE) ){
        log_error("Could not rotate texture:");
        log_error(SDL_GetError());
        return false;
    }
    return true;
}

void Image::fill(int r, int g, int b){
    Uint32 color = SDL_MapRGB(this->surface->format, r, g, b);
    SDL_FillRect(this->surface, NULL, color);
    this->update();
}


void Image::clear() {
    SDL_DestroyTexture( this->texture );
    this->texture = NULL;
    SDL_FreeSurface( this->surface );
    this->surface = NULL;
}
