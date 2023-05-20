#ifndef GAME_H
#define GAME_H

#include <qwidget.h>
#include <qevent.h>

#include <entt/entity/registry.hpp>

class Game : public QWidget 
{   
public:
    Game(QWidget* parent = nullptr);
    ~Game() = default;

    void init();

protected:
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;

private:
    enum class State {play,pause};

    entt::registry reg;
    State state = State::play;

};

#endif // GAME_H
