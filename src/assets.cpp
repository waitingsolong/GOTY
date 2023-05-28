#include "assets.h"
#include "constants.h"

#include <vector>
#include <stdexcept>

const QVector<float> angles {{qDegreesToRadians(-180.0f)},
                             {qDegreesToRadians(-150.0f)},
                             {qDegreesToRadians(-120.0f)},
                             {qDegreesToRadians(-90.0f) },
                             {qDegreesToRadians(-60.0f) },
                             {qDegreesToRadians(0.0f)   },
                             {qDegreesToRadians(30.0f)  },
                             {qDegreesToRadians(60.0f)  },
                             {qDegreesToRadians(90.0f)  },
                             {qDegreesToRadians(120.0f) },
                             {qDegreesToRadians(150.0f) },
                             {qDegreesToRadians(180.0f) }};

float getNearestAngle(QVector2D v) {
    float angle = qAtan2(v.y(), v.x());
    auto it = std::lower_bound(angles.begin(), angles.end(), angle);
    if (it == angles.end()) { 
        if (!qFuzzyCompare(angle, *angles.end())) {
            throw std::runtime_error("atan2 of (" + std::to_string(v.x()) + ',' + std::to_string(v.y()) + ") is much bigger than pi");
        }
        else {
            return *angles.end();
        }
    }

    float angleBtwAngleAndPrevious = qFabs(angle - *it);
    float angleBtwAngleAndNext     = qFabs(*(it+1) - angle);

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
    float nearestAngle = getNearestAngle(v);

    switch (bulletLabel) {
        case BULLET_LABEL_50AE:
            if (BULLET_SPRITES_50AE.find(nearestAngle) == BULLET_SPRITES_50AE.end()) {
                throw std::runtime_error("Nearest angle for vector (" + std::to_string(v.x()) + ',' + std::to_string(v.y()) + ") is not fit map: " + std::to_string(nearestAngle));
            }
            return BULLET_SPRITES_50AE[nearestAngle];
    }
}