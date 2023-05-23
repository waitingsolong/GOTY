#include <map>
#include <chrono>

// DEBUG 
#include <thread>

#include "game.h"
#include "../helpers/core/factories.h"
#include "../constants.h"
#include "../sys/physics.h"
#include "../helpers/core/setupplayer.h"
#include "../comp/player.h"
#include "../comp/velocity.h"
#include "../comp/acceleration.h"
#include <iostream>

Game::Game(QWidget* parent)
    : QGraphicsView{ parent }
{
    // set up the screen
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(SCREEN_WIDTH, SCREEN_HEIGHT);

    // set up the scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    setScene(scene);

    this->setBackgroundBrush(Qt::black);
    this->setWindowTitle("GOTY");
}

std::chrono::high_resolution_clock::time_point t1;
std::chrono::high_resolution_clock::time_point t2;
std::chrono::duration<double, std::milli> dt;

void Game::play()
{
    this->show(); 

    t1 = std::chrono::high_resolution_clock::now();

    animation_timer_.start(17, this);
}

void Game::timerEvent(QTimerEvent* event) {
    t2 = std::chrono::high_resolution_clock::now();
    dt = t2 - t1;
    std::cout << dt.count() << " ms\n";
    t1 = t2;
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

void Game::init()
{
    setupPlayer(); 
}

void Game::update()
{
    updatePhysics(reg);
}

void Game::render()
{
}

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
        //std::this_thread::sleep_for(std::chrono::milliseconds(10));
        keysPressedRightNow[event->key()] = false;
    }
}

void Game::handleInput(entt::registry& reg) {
    // DEBUG
    qDebug() << "HI! I'M HANDLE INPUT";

    //auto view = reg.view<>();
    if (keysPressedRightNow[Qt::Key_W]) {
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