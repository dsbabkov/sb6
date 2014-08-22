#include "movingtri.h"
#include <QGLShader>
#include <QGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QTime>
#include <math.h>
#include <QVector4D>

MovingTri::MovingTri(QWidget *parent) :
    QGLWidget(parent)
{
    setWindowTitle("Moving Triangle");
    time = new QTime;
    time->start();
    startTimer(33);
}

MovingTri::~MovingTri()
{
    delete time;
}

void MovingTri::initializeGL()
{
    const char * vs_source =
        "#version 410 core                                                 \n"
        "                                                                  \n"
        "layout (location = 0) in vec4 offset;                             \n"
        "                                                                  \n"
        "void main(void)                                                   \n"
        "{                                                                 \n"
        "    const vec4 vertices[] = vec4[](vec4( 0.25, -0.25, 0.5, 1.0),  \n"
        "                                   vec4(-0.25, -0.25, 0.5, 1.0),  \n"
        "                                   vec4( 0.25,  0.25, 0.5, 1.0)); \n"
        "                                                                  \n"
        "    // Add 'offset' to our hard-coded vertex position             \n"
        "    gl_Position = vertices[gl_VertexID] + offset;                 \n"
        "}                                                                 \n";
    const char * fs_source =
        "#version 410 core                             \n"
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
    program->link();

    QOpenGLVertexArrayObject* vao = new QOpenGLVertexArrayObject(this);
    vao->bind();
    program->bind();
}

void MovingTri::paintGL()
{
    GLfloat currentTime = time->elapsed() / 1000.0f;

    glClearColor(sinf(currentTime) * 0.5f + 0.5f,
                 cosf(currentTime) * 0.5f + 0.5f,
                 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);


    QVector4D attrib
    (
        sinf(currentTime) * 0.5f,
        cosf(currentTime) * 0.6f,
        0.0f,
        0.0f
    );

    program->setAttributeValue(0, attrib);

    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void MovingTri::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void MovingTri::timerEvent(QTimerEvent *)
{
    updateGL();
}
