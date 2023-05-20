#ifndef VIZUALIZER_H
#define VIZUALIZER_H

#include <qgraphicsview.h>

class Vizualizer : public QGraphicsView
{
public:
    explicit Vizualizer(QWidget *parent = nullptr);

private:
    QGraphicsScene* scene_;
};

#endif // VIZUALIZER_H
