#include "simpletexture.h"
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QPainter>
#include <QOpenGLTexture>

SimpleTexture::SimpleTexture(QWidget *parent) :
    QGLWidget(parent)
{
    setWindowTitle("Simple Texture");
    program = new QOpenGLShaderProgram(this);
    texture = new QOpenGLTexture(QOpenGLTexture::Target2D);
}

SimpleTexture::~SimpleTexture()
{
    delete texture;
}

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

    program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/simpletexture/simpletexture.vsh");
    program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/simpletexture/simpletexture.fsh");
//    program->addShaderFromSourceCode(QOpenGLShader::Fragment, fs_source);
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
