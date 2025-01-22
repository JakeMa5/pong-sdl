#include "game.h"
#include <iostream>

Game::Game()
    : window(nullptr), renderer(nullptr),
      paddle1(50, 250, 10, 100, 8), paddle2(740, 250, 10, 100, 8),
      ball(395, 295, 10, 5, 5), running(false),
      paddle1Sound(nullptr), paddle2Sound(nullptr),
      loseSound(nullptr) {}

Game::~Game() {
    cleanup();
}

bool Game::init() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        std::cerr << "SDL_Init failed: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Failed to create renderer: " << SDL_GetError() << std::endl;
        return false;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "SDL_mixer failed: " << Mix_GetError() << std::endl;
        return false;
    }

    paddle1.setColor(0, 255, 0, 255);
    paddle2.setColor(0, 0, 255, 255);

    return true;
}

void Game::loadMedia() {
    paddle1Sound = Mix_LoadWAV("gamedata/audio/soundfx/a_fx_paddle_hit_v1.wav");
    paddle2Sound = Mix_LoadWAV("gamedata/audio/soundfx/a_fx_paddle_hit_v2.wav");
    loseSound = Mix_LoadWAV("gamedata/audio/soundfx/a_fx_try_again.wav");

    if (!paddle1Sound || !paddle2Sound) {
        std::cerr << "Failed to load sound effects: " << Mix_GetError() << std::endl;
    }
}

void Game::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
        } else if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
            int vel = (event.type == SDL_KEYDOWN) ? 8 : 0;

            if (event.key.keysym.sym == SDLK_w) paddle1.setVelocity(-vel);
            if (event.key.keysym.sym == SDLK_s) paddle1.setVelocity(vel);
            if (event.key.keysym.sym == SDLK_UP) paddle2.setVelocity(-vel);
            if (event.key.keysym.sym == SDLK_DOWN) paddle2.setVelocity(vel);
        }
    }
}

void Game::update() {
    paddle1.update(600);
    paddle2.update(600);
    ball.update(800, 600);

    if (SDL_HasIntersection(&ball.getRect(), &paddle1.getRect())) {
        ball.invertX();
        Mix_PlayChannel(-1, paddle1Sound, 0);
    }

    if (SDL_HasIntersection(&ball.getRect(), &paddle2.getRect())) {
        ball.invertX();
        Mix_PlayChannel(-1, paddle2Sound, 0);
    }

    if (ball.getRect().x <= 0 || ball.getRect().x >= 800) {
        ball.reset(400, 300);
        Mix_PlayChannel(-1, loseSound, 0);
    }
}

void Game::render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    paddle1.render(renderer);
    paddle2.render(renderer);
    ball.render(renderer);

    SDL_RenderPresent(renderer);
}

void Game::run() {
    running = true;
    while (running) {
        handleEvents();
        update();
        render();
        SDL_Delay(16);
    }
}

void Game::cleanup() {
    Mix_FreeChunk(paddle1Sound);
    Mix_FreeChunk(paddle2Sound);
    Mix_FreeChunk(loseSound);
    Mix_CloseAudio();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
}
