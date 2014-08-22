#include "singletri.h"
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QPainter>

SingleTri::SingleTri(QWidget *parent) :
    QGLWidget(parent)
{
    setWindowTitle("Single Triangle");
}

void SingleTri::initializeGL()
{
    glClearColor(0.0f, 0.25f, 0.0f, 1.0f);
    const char * vs_source =
            "#version 130                                                      \n"
            "                                                                  \n"
            "void main(void)                                                   \n"
            "{                                                                 \n"
            "    const vec4 vertices[] = vec4[](vec4( 0.25, -0.25, 0.5, 1.0),  \n"
            "                                   vec4(-0.25, -0.25, 0.5, 1.0),  \n"
            "                                   vec4( 0.25,  0.25, 0.5, 1.0)); \n"
            "                                                                  \n"
            "    gl_Position = vertices[gl_VertexID];                          \n"
            "}                                                                 \n";

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

    QOpenGLVertexArrayObject* vao = new QOpenGLVertexArrayObject(this);
    vao->bind();
    program->bind();
}

void SingleTri::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void SingleTri::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}
