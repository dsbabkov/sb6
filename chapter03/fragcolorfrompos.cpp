#include "fragcolorfrompos.h"
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QPainter>

FragColorFromPos::FragColorFromPos(QWidget *parent) :
    QGLWidget(parent)
{
    setWindowTitle("Fragment color from position");
    startTimer(1000);
    interpolate = false;
}

void FragColorFromPos::initializeGL()
{
    glClearColor(0.0f, 0.25f, 0.0f, 1.0f);
    const char * vsInterpolate_source =
        "#version 420 core                                                          \n"
        "                                                                           \n"
        "void main(void)                                                            \n"
        "{                                                                          \n"
        "    const vec4 vertices[] = vec4[](vec4( 0.25, -0.25, 0.5, 1.0),           \n"
        "                                   vec4(-0.25, -0.25, 0.5, 1.0),           \n"
        "                                   vec4( 0.25,  0.25, 0.5, 1.0));          \n"
        "                                                                           \n"
        "    gl_Position = vertices[gl_VertexID];                                   \n"
        "}                                                                          \n";

    const char * fsInterpolate_source =
            "#version 420 core                                                          \n"
            "                                                                           \n"
            "out vec4 color;                                                            \n"
            "                                                                           \n"
            "void main(void)                                                            \n"
            "{                                                                          \n"
            "    color = vec4(sin(gl_FragCoord.x * 0.25) * 0.5 + 0.5,                   \n"
            "                 cos(gl_FragCoord.y * 0.25) * 0.5 + 0.5,                   \n"
            "                 sin(gl_FragCoord.x * 0.15) * cos(gl_FragCoord.y * 0.1),   \n"
            "                 1.0);                                                     \n"
            "}                                                                          \n";
    QOpenGLShader* fs = new QOpenGLShader(QOpenGLShader::Fragment);
    fs->compileSourceCode(fsInterpolate_source);

    QOpenGLShader* vs = new QOpenGLShader(QOpenGLShader::Vertex);
    vs->compileSourceCode(vsInterpolate_source);

    interpolateProgram = new QOpenGLShaderProgram(this);
    interpolateProgram->addShader(vs);
    interpolateProgram->addShader(fs);
    interpolateProgram->link();


    const char * vs_source =
        "#version 420 core                                                          \n"
        "                                                                           \n"
        "out vec4 vs_color; \n"
        "void main(void)                                                            \n"
        "{                                                                          \n"
        "    const vec4 vertices[] = vec4[](vec4( 0.25, -0.25, 0.5, 1.0),           \n"
        "                                   vec4(-0.25, -0.25, 0.5, 1.0),           \n"
        "                                   vec4( 0.25,  0.25, 0.5, 1.0));          \n"
        "    const vec4 colors[] = vec4[](vec4(1.0, 0.0, 0.0, 1.0),                 \n"
        "                                 vec4(0.0, 1.0, 0.0, 1.0),                 \n"
        "                                 vec4(0.0, 0.0, 1.0, 1.0));                \n"
        "                                                                           \n"
        "    gl_Position = vertices[gl_VertexID];                                   \n"
        "    vs_color = colors[gl_VertexID];                                        \n"
        "}                                                                          \n";

    const char * fs_source =
        "#version 420 core                                                          \n"
        "                                                                           \n"
        "in vec4 vs_color;                                                          \n"
        "out vec4 color;                                                            \n"
        "                                                                           \n"
        "void main(void)                                                            \n"
        "{                                                                          \n"
        "    color = vs_color;                                                      \n"
        "}                                                                          \n";
    fs->compileSourceCode(fs_source);

    vs->compileSourceCode(vs_source);


    nonInterpolateProgram = new QOpenGLShaderProgram(this);
    nonInterpolateProgram->addShader(vs);
    nonInterpolateProgram->addShader(fs);

    QOpenGLVertexArrayObject* vao = new QOpenGLVertexArrayObject(this);
    vao->bind();
    nonInterpolateProgram->bind();
}

void FragColorFromPos::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void FragColorFromPos::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void FragColorFromPos::timerEvent(QTimerEvent *)
{
    interpolate = !interpolate;
    if (interpolate)
        interpolateProgram->bind();
    else
        nonInterpolateProgram->bind();
    updateGL();
}
