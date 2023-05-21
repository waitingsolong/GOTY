#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include <qapplication.h>

#include "core/vizualizer.h"
#include "core/game.h"

// WHEN ADDING SIGNALS/SLOTS SET THE Q_OBJECT MACRO NOT EARLIER
// IT CAUSES BUILD ERROR

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Game game;
    game.play();
    return a.exec();
}
