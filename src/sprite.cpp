#include "sprite.h"

SpriteGroup aliveSprites;

/*
    Sprite class section

    A sprite is a class with a rect, collision detection and a image.
*/


Sprite::Sprite (int x, int y, int w, int h) {
    this->image = new Image(w, h);

    // Initializes target rect
    this->rect = {x, y, w, h};

    aliveSprites.add(this);
}

Sprite::~Sprite () {
    this->clear();
}

void Sprite::clear () {
    this->image->clear();
    aliveSprites.remove(this);
}

bool Sprite::blit(int x=0,int y=0){
    //Render texture to screen
    if (x && y) {
        rect = {x, y, this->rect.w, this->rect.h};
    }

    SDL_RenderCopy( gRenderer, this->image->texture, &this->image->rect, &rect );

    return true;
}

void Sprite::worldBlit(int cameraX, int cameraY) {
    SDL_Rect dstrect = {rect.x+cameraX,rect.y+cameraY,image->surface->w,image->surface->h};
    image->blit(&dstrect);
}

void Sprite::move(int x, int y) {
    this->rect.x = x;
    this->rect.y = y;
}
void Sprite::push(int x, int y) {
    this->rect.x += x;
    this->rect.y += y;
}

bool Sprite::pointCollide(int x,int y){
    if (// Within x interval
        x >= rect.x && x <= rect.x+rect.w &&
        // Within y interval
        y >= rect.y && y <= rect.y+rect.h)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Sprite::rectCollide(SDL_Rect collideRect){
    if (
        (this->rect.x+this->rect.w >= collideRect.x || this->rect.x<= collideRect.x+collideRect.w)
        &&
        (this->rect.y+this->rect.h >= collideRect.y || this->rect.y <= collideRect.x+collideRect.h)
       )
    {
        return true;
    }
    else
    {
        return false;
    }
}


/*
    Sprite Group section
*/

void SpriteGroup::add (Sprite* sprite) {
    this->sprites.push_back(sprite);
}

void SpriteGroup::remove (Sprite* sprite) {
    std::list<Sprite*>::iterator iter = std::find (this->sprites.begin(), this->sprites.end(), sprite );
    this->sprites.erase(iter);
}

void SpriteGroup::clear () {
    // Iterate all sprites in group
    for (std::list<Sprite*>::iterator spriteiter = this->sprites.begin();
         spriteiter != this->sprites.end(); spriteiter++){
        // Clear sprite texture and surface
        (*spriteiter)->image->clear();
    }
}

void SpriteGroup::blit () {
    for (std::list<Sprite*>::iterator spriteiter = this->sprites.begin();
         spriteiter != this->sprites.end(); spriteiter++){
        // Blit texture
        (*spriteiter)->blit();
    }
}

void SpriteGroup::worldBlit (int cameraX, int cameraY) {
    for (std::list<Sprite*>::iterator spriteiter = this->sprites.begin();
         spriteiter != this->sprites.end(); spriteiter++){
        // Blit texture
        (*spriteiter)->worldBlit(cameraX, cameraY);
    }
}

Sprite* SpriteGroup::pointCollideAny(int x,int y) {
    for (std::list<Sprite*>::iterator spriteiter = this->sprites.begin();
         spriteiter != this->sprites.end(); spriteiter++){
        // Clear sprite texture and surface
        if ((*spriteiter)->pointCollide(x, y)){
            return (*spriteiter);
        }
    }
    return NULL;
}

Sprite* SpriteGroup::rectCollideAny(SDL_Rect*) {
    return NULL;
}
