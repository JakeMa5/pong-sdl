#include "ball.h"

Ball::Ball(int x, int y, int size, int speedX, int speedY)
    : rect({x, y, size, size}), speedX(speedX), speedY(speedY) {}

void Ball::update(int screenWidth, int screenHeight) {
    rect.x += speedX;
    rect.y += speedY;

    if (rect.y <= 0 || rect.y >= screenHeight - rect.h) {
        invertY();
    }
}

void Ball::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &rect);
}

void Ball::reset(int x, int y) {
    rect.x = x;
    rect.y = y;
    speedX = (speedX > 0) ? -5 : 5;
    speedY = (speedY > 0) ? -5 : 5;
}

void Ball::invertX() {
    speedX = -speedX;
}

void Ball::invertY() {
    speedY = -speedY;
}

SDL_Rect Ball::getRect() const {
    return rect;
}
