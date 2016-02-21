#pragma once

#include "colors.h"
#include "state.h"
#include "gamecontroller.h"

class Menu: public State {
    public:
        Menu ();
        void update ();
        void blit ();
        void loop_input();
        void input (SDL_Event);
    private:
        SpriteGroup* menuSprites;
        SpriteGroup* buttonSprites;
};

extern Menu* mainMenu;

class Button: public Sprite {
    public:
        Button(int x, int y, int w, int h) : Sprite(x, y, w, h){};
        virtual void click() = 0;
};

class StartButton: public Button {
    public:
        StartButton(int x,int y,int w,int h) : Button(x, y, w, h) {}
        virtual void click(){log_debug("You clicked on the start button");}
};
