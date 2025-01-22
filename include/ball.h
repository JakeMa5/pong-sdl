#ifndef GUARD_BALL_H
#define GUARD_BALL_H

#include <SDL.h>

class Ball {
private:
    SDL_Rect rect;
    int speedX, speedY;

public:
    Ball(int x, int y, int size, int speedX, int speedY);

    void update(int screenWidth, int screenHeight);
    void render(SDL_Renderer* renderer);

    void reset(int x, int y);
    void invertX();
    void invertY();

    SDL_Rect getRect() const;
};

#endif // GUARD_BALL_H
