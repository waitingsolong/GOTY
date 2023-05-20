#ifndef VIZUALIZER_H
#define VIZUALIZER_H

#include <QtWidgets/qgraphicsview.h>

class Vizualizer : public QGraphicsView
{
    Q_OBJECT
public:
    explicit Vizualizer(QWidget *parent = nullptr);

private:
    QGraphicsScene* scene_;
};

#endif // VIZUALIZER_H
