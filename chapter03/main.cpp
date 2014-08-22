#include <QApplication>
#include "movingtri.h"
#include "tessellatedtri.h"
#include "tessellatedgstri.h"
#include "fragcolorfrompos.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MovingTri movingTri;
    TessellatedTri tessellatedTri;
    TessellatedGsTri tessellatedGsTri;
    FragColorFromPos fragColorFromPos;

//    movingTri.show();
//    tessellatedTri.show();
//    tessellatedGsTri.show();
    fragColorFromPos.show();

    return a.exec();
}
