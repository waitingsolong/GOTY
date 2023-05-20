#include "game.h"

Game::Game(){}

void Game::init() {
    const entt::entity player = makePlayer(reg);
}

void Game::keyPressEvent(QKeyEvent* event)
{
    ;
}

void Game::keyReleaseEvent(QKeyEvent* event)
{
    ;
}
