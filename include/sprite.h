#pragma once

#include <list>

#include <SDL.h>

#include "graphics.h"
#include "image.h"

class Sprite;
class SpriteGroup;

extern SpriteGroup aliveSprites;

class Sprite {
    public:
        Sprite (int,int,int,int);
        ~Sprite();
        Image* image;
        // Destination rect
        SDL_Rect rect;
        // Blitting
        bool blit (int,int);
        void worldBlit (int,int);
        void clear();
        // Delete, clean and kill sprite
        void kill ();

        // Rect manipulation
        void move(int, int);
        void push(int, int);
        // Collision
        bool pointCollide(int,int);
        bool rectCollide(SDL_Rect);
};

class SpriteGroup {
    std::list<Sprite*> sprites;

    public:
        // Management
        void add(Sprite*);
        void remove(Sprite*);
        void clear();
        // Blitting
        void blit();
        void worldBlit(int,int);
        // Collision
        Sprite* pointCollideAny(int,int);
        Sprite* rectCollideAny(SDL_Rect*);
};
