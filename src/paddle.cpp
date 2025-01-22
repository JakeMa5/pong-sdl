#include "paddle.h"

Paddle::Paddle(int x, int y, int w, int h, int speed)
    : rect({x, y, w, h}), speed(speed), velocity(0) {}

void Paddle::update(int screenHeight) {
    rect.y += velocity;

    if (rect.y < 0) rect.y = 0;
    if (rect.y > screenHeight - rect.h) rect.y = screenHeight - rect.h;
}

void Paddle::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &rect);
}

void Paddle::setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    color = {r, g, b, a};
}

void Paddle::setVelocity(int vel) {
    velocity = vel;
}

SDL_Rect Paddle::getRect() const {
    return rect;
}
