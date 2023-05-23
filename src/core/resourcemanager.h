#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <qmap.h>
#include <qpixmap.h>

class ResourceManager {
public:
    ResourceManager(); 
    
private:
    QMap<QString, QPixmap> playerSprite; 
};

#endif //RESOURCE_MANAGER_H