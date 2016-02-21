#include <string.h>

#include "font.h"

const char* fontfolder = "assets/fonts/";
//const char* fontlocation = "assets/fonts/calibri.ttf";

TTF_Font* loadFont (const char* fontname, const int size) {
    int len = strlen(fontfolder)+strlen(fontname)+1;
    char fontlocation[len];
    //fontlocation = (char*) malloc(len);
    strcpy(fontlocation, fontfolder);
    strcpy(fontlocation+strlen(fontfolder), fontname);
    fontlocation[len-1] = '\0';
    log_debug(fontlocation);
    TTF_Font* font = TTF_OpenFont( fontlocation, size );
    if( font == NULL )
    {
        log_error("Failed to load font! SDL_ttf Error: " );
        log_error(TTF_GetError());
        font = NULL;
    }
    else {
        log_debug("Successfully loaded font:");
        log_debug(fontlocation);
    }
    return font;
}
