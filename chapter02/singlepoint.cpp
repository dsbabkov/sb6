#include "singlepoint.h"
#include <QGLShader>
#include <QGLShaderProgram>
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
        "#version 420 core                             \n"
        "                                              \n"
        "void main(void)                               \n"
        "{                                             \n"
        "    gl_Position = vec4(0.0, 0.0, 0.0, 1.0);   \n"
        "}                                             \n";

    const char * fs_source =
        "#version 420 core                             \n"
        "                                              \n"
        "out vec4 color;                               \n"
        "                                              \n"
        "void main(void)                               \n"
        "{                                             \n"
        "    color = vec4(0.0, 0.8, 1.0, 1.0);         \n"
        "}                                             \n";
    QGLShader* fs = new QGLShader(QGLShader::Fragment);
    fs->compileSourceCode(fs_source);

    QGLShader* vs = new QGLShader(QGLShader::Vertex);
    vs->compileSourceCode(vs_source);

    program = new QGLShaderProgram(this);
    program->addShader(vs);
    program->addShader(fs);

//    QOpenGLVertexArrayObject* vao = new QOpenGLVertexArrayObject(this);
//    vao->bind();
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
