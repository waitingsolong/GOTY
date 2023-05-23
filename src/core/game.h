#ifndef GAME_H
#define GAME_H

#include <qgraphicsview.h>
#include <qevent.h>

#include <entt/entity/registry.hpp>
#include <QBasicTimer>

class Game : QGraphicsView
{   
    Q_OBJECT

public:
    explicit Game(QWidget* parent = nullptr);
    ~Game() = default;

    void play();

protected:
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
    void timerEvent(QTimerEvent* event) override;

private:
    enum class State {play,exit};
    enum class Busyness {hover,encounter,dialogue};

    entt::registry reg;
    State state = State::play;
    QGraphicsScene* scene;
    QBasicTimer animation_timer_;

    void init();
    void update();
    void render();

    void handleInput(entt::registry& reg);

    // gameplay 
};

#endif // GAME_H
