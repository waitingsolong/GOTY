#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QtGui/qevent.h>

#include <entt/entity/registry.hpp>

#include "factories.h"

class Game : QObject 
{
    Q_OBJECT

public:
    Game();

    void init();

private:
    enum class State {play,pause};

    entt::registry reg;
    State state = State::play;

protected:
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
};

#endif // GAME_H
