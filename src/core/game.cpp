#include "game.h"
#include "../helpers/core/factories.h"

Game::Game(QWidget* parent) : QWidget(parent) {}

void Game::init() {
    const entt::entity player = makePlayer(reg);
}

void Game::keyPressEvent(QKeyEvent* event)
{
}

void Game::keyReleaseEvent(QKeyEvent* event)
{
}
