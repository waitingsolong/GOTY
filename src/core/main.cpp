#include <qapplication.h>

#include "vizualizer.h"

// WHEN ADDING SIGNALS/SLOTS SET THE Q_OBJECT MACRO NOT EARLIER
// IT CAUSES BUILD ERROR

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Vizualizer v;
    v.setWindowTitle("GOTY");
    v.show();
    return a.exec();
}
