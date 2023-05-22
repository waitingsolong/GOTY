#ifndef GAME_H
#define GAME_H

#include <qwidget.h>
#include <qevent.h>

#include <entt/entity/registry.hpp>
#include "vizualizer.h"

class Game 
{   
public:
    ~Game() = default;

    void play();

private:
    enum class State {play,exit};
    enum class Busyness {hover,encounter,dialogue};

    entt::registry reg;
    Vizualizer v;
    State state = State::play;

    void init();
    void update();
    void render();

    void setupInput();
    void keyboard(); 
    void handleInput(entt::registry& reg);
};

#endif // GAME_H
