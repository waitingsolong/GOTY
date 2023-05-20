#include "vizualizer.h"

#include <Qt6/QtWidgets/qapplication.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Vizualizer v;
    v.setWindowTitle("GOTY");
    v.show();
    return a.exec();
}
