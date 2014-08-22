#include "singlepoint.h"
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QPainter>
#include <QDebug>

SinglePoint::SinglePoint(QWidget *parent) :
    QGLWidget(parent)
{
    setWindowTitle("Single Point");
}

void SinglePoint::initializeGL()
{
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    const char * vs_source =
        "#version 130                                  \n"
        "                                              \n"
        "void main(void)                               \n"
        "{                                             \n"
        "    gl_Position = vec4(0.0, 0.0, 0.0, 1.0);   \n"
        "}                                             \n";

    const char * fs_source =
        "#version 130                                  \n"
        "                                              \n"
        "out vec4 color;                               \n"
        "                                              \n"
        "void main(void)                               \n"
        "{                                             \n"
        "    color = vec4(0.0, 0.8, 1.0, 1.0);         \n"
        "}                                             \n";
    QOpenGLShader* fs = new QOpenGLShader(QOpenGLShader::Fragment);
    fs->compileSourceCode(fs_source);

    QOpenGLShader* vs = new QOpenGLShader(QOpenGLShader::Vertex);
    vs->compileSourceCode(vs_source);

    program = new QOpenGLShaderProgram(this);
    program->addShader(vs);
    program->addShader(fs);
    program->link();

    QOpenGLVertexArrayObject* vao = new QOpenGLVertexArrayObject(this);
    vao->bind();
    program->bind();
}

void SinglePoint::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(40.0f);
    glDrawArrays(GL_POINTS, 0, 1);
}

void SinglePoint::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}
