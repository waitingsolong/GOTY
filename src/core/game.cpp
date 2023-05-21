#include "game.h"
#include "../helpers/core/factories.h"
#include "vizualizer.h"

#include <map>

Game::Game(QWidget* parent) : QWidget(parent) {
}

void Game::play()
{
    v.show();
}

// allows simulating multiple keystrokes
std::map<int, bool> keysPressedRightNow = { {Qt::Key_W, false},
                                        {Qt::Key_A, false},
                                        {Qt::Key_S, false},
                                        {Qt::Key_D, false} };

void Game::keyPressEvent(QKeyEvent* event)
{
    if (state == State::play) {
        keysPressedRightNow[event->key()] = true;

        handlePlayerInput(event); 
    }
}

void Game::keyReleaseEvent(QKeyEvent* event)
{
    if (state == State::play) {
        keysPressedRightNow[event->key()] = false;
    }
}
