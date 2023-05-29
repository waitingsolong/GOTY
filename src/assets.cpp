#include "assets.h"
#include "constants.h"

#include <vector>
#include <algorithm>

// DEBUG
#include <qdebug.h>

int ten = 10; 

//std::vector<int> angles {{static_cast<int>(round(qDegreesToRadians(-180.0f) * ten))},
//                         {static_cast<int>(round(qDegreesToRadians(-150.0f) * ten))},
//                         {static_cast<int>(round(qDegreesToRadians(-120.0f) * ten))},
//                         {static_cast<int>(round(qDegreesToRadians(-90.0f)  * ten))},
//                         {static_cast<int>(round(qDegreesToRadians(-60.0f)  * ten))},
//                         {static_cast<int>(round(qDegreesToRadians(0.0f)    * ten))},
//                         {static_cast<int>(round(qDegreesToRadians(30.0f)   * ten))},
//                         {static_cast<int>(round(qDegreesToRadians(60.0f)   * ten))},
//                         {static_cast<int>(round(qDegreesToRadians(90.0f)   * ten))},
//                         {static_cast<int>(round(qDegreesToRadians(120.0f)  * ten))},
//                         {static_cast<int>(round(qDegreesToRadians(150.0f)  * ten))},
//                         {static_cast<int>(round(qDegreesToRadians(180.0f)  * ten))}};

std::vector<int> angles;

std::vector<float> degAngles; 

void generateAngles(int n) {
    float delta = 360.0f / static_cast<float>(n);
    degAngles.clear(); // angles from -180.0f to 180.0f with step delta 
    for (int i = 0; i <= n; i++) {
        degAngles.push_back(round(-180.0f + i * delta));
    }
    
    ten = 10; 
    while (true) {
        angles.clear();

        for (int i = 0; i < degAngles.size(); i++) {
            angles.push_back(static_cast<int>(round(qDegreesToRadians(degAngles[i]) * ten)));
        }

        // consider angles is sorted 
        // check if there are no duplicates, if they are then ten*=10 and repeat 
        bool duplicates = false;
        for (int i = 0; i < angles.size() - 1; i++) {
            if (angles[i] == angles[i + 1]) {
                duplicates = true; 
                break; 
            }
        }

        if (!duplicates) {
            break; 
        }
        ten *= 10; 
    }

    // unique int equivalents to angles are generated in angles 
}

void setupSpriteMap(QMap<int, QPixmap>& map, QString path, int q) {
    // q - amount of splits of one quarter
    int n = q * 4; // amount of splits of the whole area 
    if (angles.size() != n) {
        generateAngles(n);
    }

    QPixmap startPixmap = QPixmap(path).transformed(QTransform().rotate(-90));; // first sprite need 90 dg. It directs it with X axis
    for (int i = 1; i < angles.size(); i++) { // pass -180
        map[angles[i]] = startPixmap.transformed(QTransform().rotate(static_cast<int>(degAngles[i])));
    }
}

void setupSpritesMaps()
{
    setupSpriteMap(BULLET_SPRITES_50AE, ":bullet/50AE.png", 4);
}

// (!) change algorithm detect num size 
inline int detectTen(int randNumFromAngles) {
    // calculate count of digits - 1
    return qPow(10, (std::to_string(randNumFromAngles).size() - 1));
}

inline int getNearestAngle(QVector2D v) {
    int angle = static_cast<int>(round(qAtan2(v.y(), v.x()) * detectTen(-angles[0])));

    auto it = std::lower_bound(angles.begin(), angles.end(), angle, std::less<int>());
    if (it == angles.end() - 1 || it == angles.end()) {
        qDebug() << "krai";
        return *angles.end();
    }
    auto lb = (it == angles.begin()) ? angles.end() - 2 : it - 1;

    int angleBtwAngleAndPrevious =  std::min(qAbs(angle - *lb), 6 - qAbs(angle - *lb)); // 6 = 2pi
    int angleBtwAngleAndNext     =  std::min(qAbs(*(lb + 1) - angle) , 6 - qAbs(*(lb + 1) - angle));

    if (angleBtwAngleAndPrevious < angleBtwAngleAndNext) {
        if (lb == angles.begin()) {
            return *angles.end(); // -180 return 180 
        }

        return *lb;
    }
    else {
        return *(lb + 1);
    }
}

QPixmap getNearestPixmap(QVector2D v, int bulletLabel) {
    int nearestAngle = getNearestAngle(v);
    switch (bulletLabel) {
        case BULLET_LABEL_50AE:
            if (BULLET_SPRITES_50AE.find(nearestAngle) == BULLET_SPRITES_50AE.end()) {
                //qDebug() << "Nearest angle for vector (" + std::to_string(v.x()) + ',' + std::to_string(v.y()) + ") is not fit map: " + std::to_string(nearestAngle);
                qDebug() << "not found";
            }
            return BULLET_SPRITES_50AE[nearestAngle];
    }

    qDebug() << "Switch bullet label in getNearestPixmap() failed";
}
