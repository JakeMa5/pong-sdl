#ifndef GUARD_GAME_H
#define GUARD_GAME_H

#include <SDL.h>
#include <SDL_mixer.h>
#include "paddle.h"
#include "ball.h"

class Game {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;

    Mix_Chunk* paddle1Sound;
    Mix_Chunk* paddle2Sound;
    Mix_Chunk* loseSound;

    Paddle paddle1;
    Paddle paddle2;
    Ball ball;

    bool running;

    void handleEvents();
    void update();
    void render();

public:
    Game();
    ~Game();

    bool init();
    void loadMedia();
    void run();
    void cleanup();
};

#endif // GUARD_GAME_H
