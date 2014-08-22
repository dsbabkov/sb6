#include "simpleclear.h"

SimpleClear::SimpleClear(QWidget *parent) :
    QGLWidget(parent)
{
    setWindowTitle("Simple Clear");
}

void SimpleClear::initializeGL()
{
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
}

void SimpleClear::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
}
