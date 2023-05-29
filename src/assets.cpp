#include "assets.h"
#include "constants.h"

#include <vector>
#include <stdexcept>

// DEBUG
#include <qdebug.h>

int ten = 10; 

const QVector<int> angles {{static_cast<int>(round(qDegreesToRadians(-180.0f) * ten))},
                           {static_cast<int>(round(qDegreesToRadians(-150.0f) * ten))},
                           {static_cast<int>(round(qDegreesToRadians(-120.0f) * ten))},
                           {static_cast<int>(round(qDegreesToRadians(-90.0f)  * ten))},
                           {static_cast<int>(round(qDegreesToRadians(-60.0f)  * ten))},
                           {static_cast<int>(round(qDegreesToRadians(0.0f)    * ten))},
                           {static_cast<int>(round(qDegreesToRadians(30.0f)   * ten))},
                           {static_cast<int>(round(qDegreesToRadians(60.0f)   * ten))},
                           {static_cast<int>(round(qDegreesToRadians(90.0f)   * ten))},
                           {static_cast<int>(round(qDegreesToRadians(120.0f)  * ten))},
                           {static_cast<int>(round(qDegreesToRadians(150.0f)  * ten))},
                           {static_cast<int>(round(qDegreesToRadians(180.0f)  * ten))}};

void setupSpriteMap(QMap<int, QPixmap>& map, QString cutPath) {
    int deg = -150; 
    for (int i = 1; i < angles.size(); i++) {
       QString path = cutPath + QString::number(deg) + ".png";
        map[angles[i]] = QPixmap(path);
        deg += 30; 
    }
}

void setupSpritesMaps()
{
    setupSpriteMap(BULLET_SPRITES_50AE, ":bullet/50AE/50AE_");
}

int getNearestAngle(QVector2D v) {
    int angle = static_cast<int>(round(qAtan2(v.y(), v.x()) * ten));
    auto it = std::lower_bound(angles.begin(), angles.end(), angle);
    if (it == angles.end()) { 
        return *angles.end();
    }

    int angleBtwAngleAndPrevious = qAbs(angle - *it);
    int angleBtwAngleAndNext     = qAbs(*(it+1) - angle);

    if (angleBtwAngleAndPrevious < angleBtwAngleAndNext) {
        if (it == angles.begin()) {
            return *angles.end(); // -180 return 180 
        }

        return *it; 
    }
    else {
        return *(it + 1);
    }
}

QPixmap getNearestPixmap(QVector2D v, int bulletLabel) {
    int nearestAngle = getNearestAngle(v);
    switch (bulletLabel) {
        case BULLET_LABEL_50AE:
            if (BULLET_SPRITES_50AE.find(nearestAngle) == BULLET_SPRITES_50AE.end()) {
                qDebug() << "Nearest angle for vector (" + std::to_string(v.x()) + ',' + std::to_string(v.y()) + ") is not fit map: " + std::to_string(nearestAngle);
            }
            return BULLET_SPRITES_50AE[nearestAngle];
    }

    qDebug() << "Switch bullet label in getNearestPixmap() failed";
}
