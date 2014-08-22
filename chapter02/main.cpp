#include <QApplication>
#include "simpleclear.h"
#include "simpleclear2.h"
#include "singlepoint.h"
#include "singletri.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("OpenGL SuperBible");


//    SimpleClear simpleClear;
//    SimpleClear2 simpleClear2;
    SinglePoint singlePoint;
//    SingleTri singleTri;

//    simpleClear.show();
//    simpleClear2.show();
    singlePoint.show();
//    singleTri.show();
    return a.exec();
}
