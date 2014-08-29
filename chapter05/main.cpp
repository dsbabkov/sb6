#include <QApplication>
#include "spinnycube.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    SpinnyCube spinnyCube;

    spinnyCube.show();


    return a.exec();
}
