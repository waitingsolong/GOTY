#include <map>
#include <chrono>

// DEBUG 
#include <thread>
#include <iostream>

#include "game.h"
#include "../helpers/core/factories.h"
#include "../sys/physics.h"
#include "../helpers/core/setupplayer.h"
#include "../comp/player.h"
#include "../comp/velocity.h"
#include "../comp/acceleration.h"
#include "../comp/position.h"
#include "../comp/sprite.h"

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

std::chrono::high_resolution_clock::time_point t1;
std::chrono::high_resolution_clock::time_point t2;
std::chrono::duration<double, std::milli> dt;

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

    handleInput(reg);
    update();
    render();
}

void Game::init()
{
    setupPlayer(reg, scene);
}

void Game::update()
{
    updatePhysics(reg);
}

void updateItems(entt::registry& reg) {
    auto view = reg.view<Position, Sprite>();

    for (auto e : view) {
        auto& pos = view.get<Position>(e).pos;
        auto& sp = view.get<Sprite>(e).sp;

        sp->setPos(pos.x(), pos.y());
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
//        handleInput(reg);
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

void Game::keyPressEvent(QKeyEvent* event)
{
    qDebug() << "key press event";
    if (state == State::play) {
        keysPressedRightNow[event->key()] = true;
    }
}

void Game::keyReleaseEvent(QKeyEvent* event)
{
    qDebug() << "key release event";
    if (state == State::play) {
        //std::this_thread::sleep_for(std::chrono::milliseconds(100));
        keysPressedRightNow[event->key()] = false;
    }
}

void Game::handleInput(entt::registry& reg) {
    std::cout << "\nhandling input";

    auto view = reg.view<Player, Acceleration>();

    int keys[4]{Qt::Key_W, Qt::Key_A, Qt::Key_S ,Qt::Key_D};

    for (auto e : view) {
        auto& a = view.get<Acceleration>(e).acc;
        
        QVector2D deltaA(0.0f, 0.0f); 

        std::cout << "\ndeltaA: " << deltaA.x() << ' ' << deltaA.y();
        for (int i = 0; i < 4; i++) {
            if (keysPressedRightNow[keys[i]]) { deltaA += acceleration[keys[i]]; }
            std::cout << "\ndeltaA: " << deltaA.x() << ' ' << deltaA.y();
        }

        /*if (keysPressedRightNow[Qt::Key_W]) {
            qDebug() << "W";
        }
        if (keysPressedRightNow[Qt::Key_A]) {
            qDebug() << "A";
        }
        if (keysPressedRightNow[Qt::Key_S]) {
            qDebug() << "S";
        }
        if (keysPressedRightNow[Qt::Key_D]) {
            qDebug() << "D";
        }*/

        if (qFuzzyCompare(NULL_VECTOR, deltaA)) {
            a += deltaA.normalized() * accelerationMag; 
        }
    }

    //if (keysPressedRightNow[Qt::Key_Space]) {
    //    //dodge
    //}
    //if (keysPressedRightNow[Qt::Key_F]) {
    //    //devour
    //}
    //if (keysPressedRightNow[Qt::Key_Escape]) {
    //    state = State::exit;
    //}
}