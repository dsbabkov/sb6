#include <QApplication>
#include "spinnycube.h"
#include "simpletexture.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    SpinnyCube spinnyCube;
    SimpleTexture simpleTexture;

//    spinnyCube.show();
    simpleTexture.show();

    return a.exec();
}
