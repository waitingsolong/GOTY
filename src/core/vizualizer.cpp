#include "vizualizer.h"

Vizualizer::Vizualizer(QWidget *parent)
    : QGraphicsView{parent}
{
    // set up the screen
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1024,768);

    // set up the scene
    scene_ = new QGraphicsScene();
    scene_->setSceneRect(0,0,1024,768);
    setScene(scene_);

    this->setBackgroundBrush(Qt::black);
}
