#include "simpleclear2.h"
#include "math.h"
#include <QTime>

SimpleClear2::SimpleClear2(QWidget *parent) :
    QGLWidget(parent)
{
    r = g = 0.0f;
    time = new QTime;
    time->start();
    setWindowTitle("Simple Clear 2");
    startTimer(33);
}
SimpleClear2::~SimpleClear2()
{
    delete time;
}

void SimpleClear2::initializeGL()
{
}

void SimpleClear2::paintGL()
{
    glClearColor(r, g, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void SimpleClear2::timerEvent(QTimerEvent*)
{
    double elapsed = time->elapsed() / 1000.0;
    r = sin(elapsed) * 0.5f + 0.5f;
    g = cos(elapsed) * 0.5f + 0.5f;
    updateGL();
}
