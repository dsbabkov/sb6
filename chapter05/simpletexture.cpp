#include "simpletexture.h"
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QPainter>
#include <QOpenGLTexture>

const char* vs_source =
    "#version 420 core                                                              \n"
    "                                                                               \n"
    "void main(void)                                                                \n"
    "{                                                                              \n"
    "    const vec4 vertices[] = vec4[](vec4( 0.75, -0.75, 0.5, 1.0),               \n"
    "                                   vec4(-0.75, -0.75, 0.5, 1.0),               \n"
    "                                   vec4( 0.75,  0.75, 0.5, 1.0));              \n"
    "                                                                               \n"
    "    gl_Position = vertices[gl_VertexID];                                       \n"
    "}                                                                              \n";
const char* fs_source =
    "#version 430 core                                                              \n"
    "                                                                               \n"
    "uniform sampler2D s;                                                           \n"
    "                                                                               \n"
    "out vec4 color;                                                                \n"
    "                                                                               \n"
    "void main(void)                                                                \n"
    "{                                                                              \n"
    "    color = texture(s, gl_FragCoord.xy / textureSize(s, 0));                   \n"
    "}                                                                              \n";

SimpleTexture::SimpleTexture(QWidget *parent) :
    QGLWidget(parent)
{
    setWindowTitle("Simple Texture");
    program = new QOpenGLShaderProgram(this);
    texture = new QOpenGLTexture(QOpenGLTexture::Target2D);
}

//SimpleTexture::~SimpleTexture()
//{
//    delete texture;
//}

void SimpleTexture::initializeGL()
{
    glClearColor(0.0f, 0.25f, 0.0f, 1.0f);

    texture->create();
    texture->bind();
    texture->setMipLevels(8);
    texture->setFormat(QOpenGLTexture::RGBA32F);
    texture->setSize(256, 256);
    texture->allocateStorage();


    float data[256 * 256 * 4];
    generate_texture(data, 256, 256);

    texture->setData(QOpenGLTexture::RGBA, QOpenGLTexture::Float32, data);

    program->addShaderFromSourceCode(QOpenGLShader::Vertex, vs_source);
    program->addShaderFromSourceCode(QOpenGLShader::Fragment, fs_source);
    program->bind();
}

void SimpleTexture::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void SimpleTexture::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}
