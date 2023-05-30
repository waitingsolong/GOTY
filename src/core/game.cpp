#include <map>
#include <chrono>

// DEBUG 
#include <thread>
#include <iostream>

#include "game.h"
#include "../helpers/core/factories.h"
#include "../sys/physics.h"
#include "../comp/player.h"
#include "../comp/velocity.h"
#include "../comp/acceleration.h"
#include "../comp/position.h"
#include "../comp/sprite.h"
#include "../sys/combat.h"
#include "../assets.h"

Game::Game(QWidget* parent)
    : QGraphicsView{ parent }
{
    // set up the screen
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFrameStyle(0);
    setFixedSize(SCREEN_WIDTH + 2 * this->frameWidth(), SCREEN_HEIGHT + 2 * this->frameWidth());

    // set up the scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, SCREEN_WIDTH + 2 * this->frameWidth(), SCREEN_HEIGHT + 2 * this->frameWidth());
    setScene(scene);
    fitInView(scene->sceneRect(), Qt::KeepAspectRatio);

    this->setBackgroundBrush(Qt::black);
    this->setWindowTitle("GOTY");
}

void Game::play()
{
    init();

    show(); 

    //t1 = std::chrono::high_resolution_clock::now();

    animation_timer_.start(MS_PER_FRAME, this);
}

void Game::timerEvent(QTimerEvent* event) {
    //
    // TIME MEASURING 
    // 
    
    //t2 = std::chrono::high_resolution_clock::now();
    //dt = t2 - t1;
    //std::cout << dt.count() << " ms\n";
    //t1 = t2;

    updateInput(reg);
    update();
    render();
}

void Game::init()
{
    setupPlayer(reg);
    setupSpritesMaps();
}

void Game::update()
{
    updatePhysics(reg);
}

void Game::updateItems(entt::registry& reg) {
    auto view = reg.view<Position, Sprite>();

    for (auto e : view) {
        auto& pos = view.get<Position>(e).pos;
        auto& sp = view.get<Sprite>(e).sp;

        QPointF scenePos = this->mapToScene(pos.x(), pos.y());
        sp->setPos(scenePos);
    }
}

void Game::render()
{
    updateItems(reg);
    scene->update();
}

//
//
// ANOTHER GAMELOOP IMPLEMENTATION. PROBABLY WILL BE INSERTED LATER
//
// 

//void Game::play()
//{
//    init();
//
//    this->show();
//
//    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
//    std::chrono::high_resolution_clock::time_point t2;
//    std::chrono::duration<double, std::milli> dt; 
//    double lag = 0.0;
//
//    while (state != State::exit) {
//        t2 = std::chrono::high_resolution_clock::now();
//        dt = t2 - t1;
//        lag += dt.count();
//        t1 = t2;
//
//        updateInput(reg);
//
//        //while code is small it will work a very long time
//        while (lag >= MS_PER_FRAME) {
//            update();
//            lag -= MS_PER_FRAME;
//        }
//
//        render();
//    }
//}

//
//
//
// INPUT HANDLING
//
//

// for multiple presses processing 
std::map<int, bool> keysPressedRightNow = { {Qt::Key_W, false},
                                        {Qt::Key_A, false},
                                        {Qt::Key_S, false},
                                        {Qt::Key_D, false} };

std::map<int, bool> buttonsPressedRightNow = { {Qt::MouseButton::LeftButton, false},
                                        {Qt::MouseButton::RightButton, false} };

std::map<int, bool> buttonsReleasedRightNow = { {Qt::MouseButton::LeftButton, false},
                                        {Qt::MouseButton::RightButton, false} };

void Game::keyPressEvent(QKeyEvent* event)
{
    if (state == State::play) {
        keysPressedRightNow[event->key()] = true;
    }
}

void Game::keyReleaseEvent(QKeyEvent* event)
{
    if (state == State::play) {
        keysPressedRightNow[event->key()] = false;
    }
}

void Game::mousePressEvent(QMouseEvent* event) {
    if (state == State::play) {
        buttonsPressedRightNow[event->button()] = true;
    }
}

void Game::mouseReleaseEvent(QMouseEvent* event) {
    if (state == State::play) {
        buttonsReleasedRightNow[event->button()] = true;
    }
}

inline bool bothOfCoordsAreNotZero(QVector2D v) {
    return (v.x() != 0.0f || v.y() != 0.0f) ? true : false;
}

void Game::updateInput(entt::registry& reg) {

    auto view = reg.view<Player, Acceleration, Velocity, Position>();

    int keys[4]{ Qt::Key_W, Qt::Key_A, Qt::Key_S ,Qt::Key_D };

    for (auto e : view) {
        auto& a = view.get<Acceleration>(e).acc;

        QVector2D deltaA(0.0f, 0.0f);

        for (int i = 0; i < 4; i++) {
            if (keysPressedRightNow[keys[i]]) { deltaA += acceleration[keys[i]]; }
        }

        a = (bothOfCoordsAreNotZero(deltaA)) ? deltaA.normalized() * accelerationMag : deltaA;
    }

    // 0..9 - 48..57
    for (int i = 48; i < 58; i++) {
        if (keysPressedRightNow[i]) {
            selectWeapon(reg, i-48, this);
        }
    }

    if (keysPressedRightNow[Qt::Key_R]) {
        putOffWeapon(reg);
    }
    
    //if (keysPressedRightNow[Qt::Key_Escape]) {
    //    state = State::exit;
    //}

    //
    // clicks
    //

    if (buttonsPressedRightNow[Qt::MouseButton::LeftButton]) {
        buttonsPressedRightNow[Qt::MouseButton::LeftButton] = false;
        startShoot(reg);
    } 
    else if (buttonsReleasedRightNow[Qt::MouseButton::LeftButton]) {
        buttonsReleasedRightNow[Qt::MouseButton::LeftButton] = false;
        stopShoot(reg);
    }
}
