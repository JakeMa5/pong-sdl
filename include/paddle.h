#ifndef GUARD_PADDLE_H
#define GUARD_PADDLE_H

#include <SDL.h>

class Paddle {
private:
    SDL_Rect rect;
    int speed;
    int velocity;
    SDL_Color color;

public:
    Paddle(int x, int y, int w, int h, int speed);

    void update(int screenHeight);
    void render(SDL_Renderer* renderer);

    void setVelocity(int vel);

    void setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

    SDL_Rect getRect() const;
};

#endif // GUARD_PADDLE_H
