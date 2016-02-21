#include "states/menu.h"

Menu* mainMenu;

Button::Button (int x, int y, int w, int h) : Sprite(x, y, w, h) {
    //mainMenu->buttonSprites->add(this);
}

void StartButton::click(){
    log_debug("Clicked on the button");
}


Menu::Menu(){
    log_debug("Loading menu state");

    menuSprites = new SpriteGroup();
    buttonSprites = new SpriteGroup();

    int w, h, x, y;

    w = 350;
    h = 75;
    x = (SCREEN_SIZE[0]/2)-(w/2);
    y = 100;
    Sprite* welcomeText = new Sprite(x, y, w, h);
    welcomeText->image->fill(COLOR_WHITE.r, COLOR_WHITE.g, COLOR_WHITE.b);
    welcomeText->image->loadText("An game", gFontHuge, COLOR_BLACK, COLOR_WHITE);
    //welcomeText->image->rotate(10.0);
    menuSprites->add(welcomeText);

    w = 300;
    h = 75;
    x = (SCREEN_SIZE[0]/2)-(w/2);
    y = 200;
    StartButton* startButton = new StartButton(x, y, w, h);
    startButton->image->fill(150,150,150);
    startButton->image->loadText("New Game", gFont, COLOR_BLACK, COLOR_GRAY);
    menuSprites->add(startButton);
    buttonSprites->add(startButton);
}

void Menu::update(){
    // Background color
    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
    loop_input();
}

void Menu::blit () {
	menuSprites->blit();
}

void Menu::loop_input () {
    if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_A)){
        log_debug("Pressed A");
    }
}

void Menu::input (SDL_Event e) {
    //User presses a key
    if( e.type == SDL_KEYDOWN ){
        switch( e.key.keysym.sym )
        {
            case SDLK_RETURN:
                log_debug("Pressed Enter");
                //aliveSprites.clear();
                break;
            default:
                break;
        }
    }

    else if ( e.type == SDL_MOUSEBUTTONDOWN ) {
    	if ( e.button.button == SDL_BUTTON_LEFT ){
            Sprite* button = this->buttonSprites->pointCollideAny(e.button.x, e.button.y);
            if (button){
                log_debug("Pressed LMB");
            }
    	}
    }
}
