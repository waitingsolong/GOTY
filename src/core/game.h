#ifndef GAME_H
#define GAME_H

#include <qgraphicsview.h>
#include <qevent.h>
#include <qobject.h>

#include <entt/entity/registry.hpp>
#include <QBasicTimer>
#include "../constants.h"

class Game : public QGraphicsView
{   
    Q_OBJECT

public:
    explicit Game(QWidget* parent = nullptr);
    ~Game() = default;

    void play();

    QGraphicsScene* scene;

public slots:
    void shoot();

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override; 
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
    void timerEvent(QTimerEvent* event) override;

private:
    enum class State {play,exit};
    enum class Busy {hover,encounter,dialogue};

    entt::registry reg;
    State state = State::play;
    Busy busy = Busy::hover; 
    QBasicTimer animation_timer_;

    void init();
    void update();
    void render();

    void updateItems(entt::registry& reg);
    void updateInput(entt::registry& reg);

    //
    // setups
    //

    void equip(entt::registry& reg);
    void setupPlayer(entt::registry& reg);

    //
    // gameplay 
    //

    QMap<int, QVector2D> acceleration = { {Qt::Key_W, QVector2D(0, -PLAYER_BASIC_ACCELERATION_M)},
                                        {Qt::Key_A, QVector2D(-PLAYER_BASIC_ACCELERATION_M, 0)},
                                        {Qt::Key_S, QVector2D(0, PLAYER_BASIC_ACCELERATION_M)},
                                        {Qt::Key_D, QVector2D(PLAYER_BASIC_ACCELERATION_M, 0)} };

    float accelerationMag = PLAYER_BASIC_ACCELERATION_M;
};

#endif // GAME_H
