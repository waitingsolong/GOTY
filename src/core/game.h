#ifndef GAME_H
#define GAME_H

#include <qwidget.h>
#include <qevent.h>

#include <entt/entity/registry.hpp>
#include "vizualizer.h"

class Game : public QWidget 
{   
public:
    Game(QWidget* parent = nullptr);
    ~Game() = default;

    void play();

protected:
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;

private:
    enum class State {play,exit};
    enum class Busyness {hover,encounter,dialogue};

    entt::registry reg;
    Vizualizer v;
    State state = State::play;

    bool input = false;
    void init();
    void update();
    void render();
};

#endif // GAME_H
