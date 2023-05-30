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
    for (int i = 1; i <= n; i++) {
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

    QPixmap startPixmap = QPixmap(path).transformed(QTransform().rotate(90)); // rotate 90 deg counterclockwise to adapt coordinate system to qt's
    for (int i = 0; i < angles.size(); i++) { // pass -180
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

// (!) no sense in calculating localTen every time. It depends on selected weapon 
inline int getNearestAngle(QVector2D v) {
    int localTen = detectTen(-angles[0]); 
    int translated2PI = static_cast<int>(round(M_PI * localTen));

    int angle = static_cast<int>(round(qAtan2(v.y(), v.x()) * localTen));

    auto lb = angles.begin();
    while (angle > *lb && lb != angles.end()) {
        lb++;
    }
    if (lb == angles.end()) {
        qDebug() << "ERROR. Why?";
    }

    std::vector<int>::iterator rb;
    if (lb == angles.begin()) {
        lb = angles.end() - 1;
        rb = angles.begin();
    }
    else {
        rb = lb;
        lb--;
    }
    
    auto delta1 = qAbs(*lb - angle); 
    auto delta2 = qAbs(angle - *rb);
    delta1 = std::min(delta1, translated2PI - delta1);
    delta2 = std::min(delta2, translated2PI - delta2);

    if (delta1 < delta2) {
        return *lb;
    }
    else {
        return *rb; 
    }
}

QPixmap getNearestPixmap(QVector2D v, int bulletLabel) {
    int nearestAngle = getNearestAngle(v);
    switch (bulletLabel) {
        case BULLET_LABEL_50AE:
            if (BULLET_SPRITES_50AE.find(nearestAngle) == BULLET_SPRITES_50AE.end()) {
                qDebug() << "not found";
            }
            return BULLET_SPRITES_50AE[nearestAngle];
    }

    qDebug() << "ERROR. Switch bullet label in getNearestPixmap() failed";
}
