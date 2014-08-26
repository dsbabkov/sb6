#include "spinnycube.h"
#include <QOpenGLShader>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QMatrix4x4>
#include <QDebug>

SpinnyCube::SpinnyCube(QWidget *parent) :
    QGLWidget(parent)
{
    setWindowTitle("Spinny Cube");
    proj_matrix = new QMatrix4x4;
    qDebug() << proj_matrix->isIdentity();
}
SpinnyCube::~SpinnyCube()
{
    delete proj_matrix;
}

void SpinnyCube::initializeGL()
{
    glClearColor(0.0f, 0.25f, 0.0f, 1.0f);
    glClearDepth(1.0f);

    const char * vs_source =
        "#version 410 core                                                  \n"
        "                                                                   \n"
        "in vec4 position;                                                  \n"
        "                                                                   \n"
        "out VS_OUT                                                         \n"
        "{                                                                  \n"
        "    vec4 color;                                                    \n"
        "} vs_out;                                                          \n"
        "                                                                   \n"
        "uniform mat4 mv_matrix;                                            \n"
        "uniform mat4 proj_matrix;                                          \n"
        "                                                                   \n"
        "void main(void)                                                    \n"
        "{                                                                  \n"
        "    gl_Position = proj_matrix * mv_matrix * position;              \n"
        "    vs_out.color = position * 2.0 + vec4(0.5, 0.5, 0.5, 0.0);      \n"
        "}                                                                  \n";

    const char * fs_source =
        "#version 410 core                                                  \n"
        "                                                                   \n"
        "out vec4 color;                                                    \n"
        "                                                                   \n"
        "in VS_OUT                                                          \n"
        "{                                                                  \n"
        "    vec4 color;                                                    \n"
        "} fs_in;                                                           \n"
        "                                                                   \n"
        "void main(void)                                                    \n"
        "{                                                                  \n"
        "    color = fs_in.color;                                           \n"
        "}                                                                  \n";

    program = new QOpenGLShaderProgram(this);

    program->addShaderFromSourceCode(QOpenGLShader::Fragment, fs_source);
    program->addShaderFromSourceCode(QOpenGLShader::Vertex, vs_source);
    program->link();

    mv_location = program->uniformLocation("mv_matrix");
    proj_location = program->uniformLocation("proj_matrix");



    QOpenGLVertexArrayObject* vao = new QOpenGLVertexArrayObject(this);
    vao->create();
    vao->bind();

    const GLfloat vertex_positions[] =
    {
        -0.25f,  0.25f, -0.25f,
        -0.25f, -0.25f, -0.25f,
         0.25f, -0.25f, -0.25f,

         0.25f, -0.25f, -0.25f,
         0.25f,  0.25f, -0.25f,
        -0.25f,  0.25f, -0.25f,

         0.25f, -0.25f, -0.25f,
         0.25f, -0.25f,  0.25f,
         0.25f,  0.25f, -0.25f,

         0.25f, -0.25f,  0.25f,
         0.25f,  0.25f,  0.25f,
         0.25f,  0.25f, -0.25f,

         0.25f, -0.25f,  0.25f,
        -0.25f, -0.25f,  0.25f,
         0.25f,  0.25f,  0.25f,

        -0.25f, -0.25f,  0.25f,
        -0.25f,  0.25f,  0.25f,
         0.25f,  0.25f,  0.25f,

        -0.25f, -0.25f,  0.25f,
        -0.25f, -0.25f, -0.25f,
        -0.25f,  0.25f,  0.25f,

        -0.25f, -0.25f, -0.25f,
        -0.25f,  0.25f, -0.25f,
        -0.25f,  0.25f,  0.25f,

        -0.25f, -0.25f,  0.25f,
         0.25f, -0.25f,  0.25f,
         0.25f, -0.25f, -0.25f,

         0.25f, -0.25f, -0.25f,
        -0.25f, -0.25f, -0.25f,
        -0.25f, -0.25f,  0.25f,

        -0.25f,  0.25f, -0.25f,
         0.25f,  0.25f, -0.25f,
         0.25f,  0.25f,  0.25f,

         0.25f,  0.25f,  0.25f,
        -0.25f,  0.25f,  0.25f,
        -0.25f,  0.25f, -0.25f
    };

    QOpenGLBuffer* buffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    buffer->create();
    qDebug() << "Buffer is bond: " << buffer->bind();
    buffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
    buffer->allocate(vertex_positions, sizeof(vertex_positions));

    program->setAttributeArray(0, GL_FLOAT, 0, 3);
    program->enableAttributeArray(0);

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

}

void SpinnyCube::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    program->bind();

    program->setUniformValueArray(proj_location, proj_matrix, 1);

    QMatrix4x4 mv_matrix;
    program->setUniformValueArray(mv_location, &mv_matrix, 1);

    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void SpinnyCube::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    float aspect = static_cast<float>(w) / static_cast<float>(h);
    *proj_matrix = QMatrix4x4();
    proj_matrix->perspective(50.0f, aspect, 0.1f, 1000.0f);
}
