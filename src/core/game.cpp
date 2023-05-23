#include <map>
#include <chrono>
#include <SDL.h>

// DEBUG 
#include <thread>

#include "game.h"
#include "../helpers/core/factories.h"
#include "vizualizer.h"
#include "../constants.h"
#include "../sys/physics.h"
#include "../helpers/core/setupplayer.h"
#include "../comp/player.h"
#include "../comp/velocity.h"
#include "../comp/acceleration.h"
#include <iostream>

void Game::play()
{
    init();

    v.show();

    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    std::chrono::high_resolution_clock::time_point t2;
    std::chrono::duration<double, std::milli> dt; 
    double lag = 0.0;

    while (state != State::exit) {
        t2 = std::chrono::high_resolution_clock::now();
        dt = t2 - t1;
        lag += dt.count();
        t1 = t2;

        handleInput(reg);

        //while code is small it will work a very long time
        while (lag >= MS_PER_FRAME) {
            update();
            lag -= MS_PER_FRAME;
        }

        render();
    }
}

void Game::init()
{
    setupPlayer(); 
    setupInput();
}

void Game::update()
{
    updatePhysics(reg);
}

void Game::render()
{
}

//
//
//
// INPUT HANDLING
//
//

const Uint8* actualKeys = SDL_GetKeyboardState(NULL);

bool keystroke[SDL_KEYMAP_SIZE];

void Game::setupInput() {
    memset(keystroke, 0, SDL_KEYMAP_SIZE);
}

void Game::handleInput(entt::registry& reg) {
    // DEBUG
    qDebug() << "WAITING FOR YOU PRESS KEYS";
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    SDL_PumpEvents();

    SDL_Event event;
    while (SDL_PollEvent(&event)) { 
        qDebug() << "SDL EVENT";
        switch (event.type) {
        case SDL_KEYDOWN:
            qDebug() << "KEYDOWN";
            keystroke[event.key.keysym.scancode] = true;
            break;
        case SDL_KEYUP:
            qDebug() << "KEYUP";
            keystroke[event.key.keysym.scancode] = false;
            break;
        case SDL_QUIT:
            state = State::exit;
            break;
        }
    }

    // movement 
    auto view = reg.view<Player, Acceleration>();

    for (auto e : view) {
        auto& a = view.get<Acceleration>(e).acc;
    }

    if (actualKeys[SDL_SCANCODE_W]) {
        qDebug() << "w";
    }
    if (actualKeys[SDL_SCANCODE_A]) {
        qDebug() << "a";
    }
    if (actualKeys[SDL_SCANCODE_S]) {
        qDebug() << "s";
    }
    if (actualKeys[SDL_SCANCODE_D]) {
        qDebug() << "d";
    }

    if (actualKeys[SDL_SCANCODE_ESCAPE]) {
        state = State::exit;
    }
}