#include "spinnycube.h"
#include <QOpenGLShader>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QMatrix4x4>
#include <QDebug>
#include <QTime>
#include <math.h>

SpinnyCube::SpinnyCube(QWidget *parent) :
    QGLWidget(parent)
{
    setWindowTitle("Spinny Cube");

    proj_matrix = new QMatrix4x4;
    program = new QOpenGLShaderProgram;
    time = new QTime;
    many = false;
    time->start();
    startTimer(16);
}
SpinnyCube::~SpinnyCube()
{
    delete proj_matrix;
    delete time;
}

void SpinnyCube::initializeGL()
{
//    initializeOpenGLFunctions();
    glClearColor(0.0f, 0.25f, 0.0f, 1.0f);
    glClearDepth(1.0f);

    const char * vs_source =
    {
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
        "}                                                                  \n"
    };

    const char * fs_source =
    {
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
        "}                                                                  \n"
    };

    program->addShaderFromSourceCode(QOpenGLShader::Fragment, fs_source);
    program->addShaderFromSourceCode(QOpenGLShader::Vertex, vs_source);
    program->link();

    mv_location = program->uniformLocation("mv_matrix");
    proj_location = program->uniformLocation("proj_matrix");

//    QOpenGLVertexArrayObject* vao = new QOpenGLVertexArrayObject(this);
//    vao->bind();

    static const GLfloat vertex_positions[] =
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

    QOpenGLBuffer* buffer = new QOpenGLBuffer;
    buffer->create();
    buffer->bind();
    buffer->allocate(vertex_positions, sizeof(vertex_positions));
    buffer->setUsagePattern(QOpenGLBuffer::StaticDraw);

    program->setAttributeArray(0, GL_FLOAT, NULL, 3);
    program->enableAttributeArray(0);

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

}


void SpinnyCube::paintGL()
{
    float currentTime = time->elapsed() / 1000.0f;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    program->bind();
    program->setUniformValue(proj_location, *proj_matrix);

    if (many)
    {
        int i;
        for (i = 0; i < 24; i++)
        {
            float f = i + currentTime * 0.3f;
            QMatrix4x4 mv_matrix;
            mv_matrix.translate(0.0f, 0.0f, -6.0f);
            mv_matrix.rotate(currentTime * 45.0f, 0.0f, 1.0f, 0.0f);
            mv_matrix.rotate(currentTime * 21.0f, 1.0f, 0.0f, 0.0f);
            mv_matrix.translate(sinf(2.1f * f) * 2.0f,
                                cosf(1.7f * f) * 2.0f,
                                sinf(1.3f * f) * cosf(1.5f * f) * 2.0f);
            program->setUniformValue(mv_location, mv_matrix);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
    }
    else
    {
        float f = currentTime * 0.3f;
        QMatrix4x4 mv_matrix;
        mv_matrix.translate(0.0f, 0.0f, -4.0f);
        mv_matrix.translate(sinf(2.1f * f) * 0.5f,
                            cosf(1.7f * f) * 0.5f,
                            sinf(1.3f * f) * cosf(1.5f * f) * 2.0f);
        mv_matrix.rotate(currentTime * 45.0f, 0.0f, 1.0f, 0.0f);
        mv_matrix.rotate(currentTime * 81.0f, 1.0f, 0.0f, 0.0f);
        program->setUniformValue(mv_location, mv_matrix);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}

void SpinnyCube::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    float aspect = static_cast<float>(w) / static_cast<float>(h);
    proj_matrix->setToIdentity();
    proj_matrix->perspective(50.0f, aspect, 0.1f, 1000.0f);
}

void SpinnyCube::timerEvent(QTimerEvent *)
{
    if (time->elapsed() % 4000 < 2000)
        many = false;
    else
        many = true;
    updateGL();
}
