#include <map>
#include <chrono>

#include "game.h"
#include "../helpers/core/factories.h"
#include "vizualizer.h"
#include "../constants.h"

// for debug
#include <Windows.h>
#include <iostream>
#include <thread>

Game::Game(QWidget* parent) : QWidget(parent) {}

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
        t1 = t2; 

        lag += dt.count();

        input = true;
        // maybe add sleep if several keys do not work 

        //while code is small it will work a very long time
        while (lag >= MS_PER_FRAME) {
            update();
            lag -= MS_PER_FRAME;
        }

        render();
    }
}

// allows simulating multiple keystrokes
std::map<int, bool> keysPressedRightNow = { {Qt::Key_W, false},
                                        {Qt::Key_A, false},
                                        {Qt::Key_S, false},
                                        {Qt::Key_D, false} };

void Game::keyPressEvent(QKeyEvent* event)
{
    if (input && state == State::play) {
        keysPressedRightNow[event->key()] = true;

        //auto view = reg.view<>();
        if (keysPressedRightNow[Qt::Key_W]) {
        }
        if (keysPressedRightNow[Qt::Key_A]) {
        }
        if (keysPressedRightNow[Qt::Key_S]) {
        }
        if (keysPressedRightNow[Qt::Key_D]) {
        }
        if (keysPressedRightNow[Qt::Key_Space]) {
            //dodge
        }
        if (keysPressedRightNow[Qt::Key_F]) {
            //devour
        }
        if (keysPressedRightNow[Qt::Key_Escape]) {
            state = State::exit;
        }
    }
}

void Game::keyReleaseEvent(QKeyEvent* event)
{
    if (input) {
        keysPressedRightNow[event->key()] = false;
        input = false; 
    }

}

void Game::init()
{
}

void Game::update()
{
}

void Game::render()
{
}
