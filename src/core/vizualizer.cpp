#include "vizualizer.h"
#include "../constants.h"

Vizualizer::Vizualizer(QWidget *parent)
    : QGraphicsView{parent}
{
    // set up the screen
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(SCREEN_WIDTH, SCREEN_HEIGHT);

    // set up the scene
    scene_ = new QGraphicsScene();
    scene_->setSceneRect(0,0, SCREEN_WIDTH, SCREEN_HEIGHT);
    setScene(scene_);

    this->setBackgroundBrush(Qt::black);
    this->setWindowTitle("GOTY");
}
