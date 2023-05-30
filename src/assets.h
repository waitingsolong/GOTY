#ifndef ASSETS_H
#define ASSETS_H

#include <qmap.h>
#include <qpixmap.h>
#include <qvector2d.h>

// DEBUG
int getNearestAngle(QVector2D v);

void setupSpritesMaps();

QPixmap getNearestPixmap(QVector2D, int); 

static QMap<int, QPixmap> BULLET_SPRITES_50AE; // int: rad * ten

#endif //ASSETS_H