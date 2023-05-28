#ifndef ASSETS_H
#define ASSETS_H

#include <qmap.h>
#include <qpixmap.h>
#include <qvector2d.h>

QPixmap getNearestPixmap(QVector2D, int); 

const QMap<float, QPixmap> BULLET_SPRITES_50AE {
    { qDegreesToRadians(0.0f),    QPixmap(":bullet/50AE/50AE_0.png") },
    { qDegreesToRadians(30.0f),   QPixmap(":bullet/50AE/50AE_30.png") },
    { qDegreesToRadians(60.0f),   QPixmap(":bullet/50AE/50AE_60.png") },
    { qDegreesToRadians(90.0f),   QPixmap(":bullet/50AE/50AE_90.png") },
    { qDegreesToRadians(120.0f),  QPixmap(":bullet/50AE/50AE_120.png") },
    { qDegreesToRadians(150.0f),  QPixmap(":bullet/50AE/50AE_150.png") },
    { qDegreesToRadians(180.0f),  QPixmap(":bullet/50AE/50AE_180.png") },
    { qDegreesToRadians(-150.0f), QPixmap(":bullet/50AE/50AE_-150.png") },
    { qDegreesToRadians(-120.0f), QPixmap(":bullet/50AE/50AE_-120.png") },
    { qDegreesToRadians(-90.0f),  QPixmap(":bullet/50AE/50AE_-90.png") },
    { qDegreesToRadians(-60.0f),  QPixmap(":bullet/50AE/50AE_-60.png") },
    { qDegreesToRadians(-30.0f),  QPixmap(":bullet/50AE/50AE_-30.png") }
};

#endif //ASSETS_H