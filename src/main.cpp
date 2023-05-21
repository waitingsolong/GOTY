#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup") // off cmd 

#include <qapplication.h>
#include <qdebug.h>

#include "core/vizualizer.h"
#include "core/game.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Game game;
    game.play();
    return a.exec();
}

// is there a way to unite two items but only their textures and 
// handle them like separate when register collisions? 

// WHEN ADDING SIGNALS/SLOTS SET THE Q_OBJECT MACRO NOT EARLIER
// IT CAUSES BUILD ERROR

// qreal convert to float only in arm, vec2d, vec3d. Maybe it makes sense 
// to set Qt configure flag -qreal float 

// whether use shape override method method on player every frame and find intersection 
// of bullet items with every time drawing ellipse or 
// just move two different items of hitbox and sprite separately 
