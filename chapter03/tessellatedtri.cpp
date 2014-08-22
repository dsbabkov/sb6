#include "tessellatedtri.h"
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>

TessellatedTri::TessellatedTri(QWidget *parent) :
    QGLWidget(parent)
{
    setWindowTitle("Tessellated Triangle");
}

void TessellatedTri::initializeGL()
{
    glClearColor(0.0f, 0.25f, 0.0f, 1.0f);
    const char * vs_source =
        "#version 420 core                                                 \n"
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
        "#version 420 core                             \n"
        "                                              \n"
        "out vec4 color;                               \n"
        "                                              \n"
        "void main(void)                               \n"
        "{                                             \n"
        "    color = vec4(0.0, 0.8, 1.0, 1.0);         \n"
        "}                                             \n";

    const char * tcs_source =
        "#version 420 core                                                                 \n"
        "                                                                                  \n"
        "layout (vertices = 3) out;                                                        \n"
        "                                                                                  \n"
        "void main(void)                                                                   \n"
        "{                                                                                 \n"
        "    if (gl_InvocationID == 0)                                                     \n"
        "    {                                                                             \n"
        "        gl_TessLevelInner[0] = 5.0;                                               \n"
        "        gl_TessLevelOuter[0] = 5.0;                                               \n"
        "        gl_TessLevelOuter[1] = 5.0;                                               \n"
        "        gl_TessLevelOuter[2] = 5.0;                                               \n"
        "    }                                                                             \n"
        "    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;     \n"
        "}                                                                                 \n";

    const char * tes_source =
        "#version 420 core                                                                 \n"
        "                                                                                  \n"
        "layout (triangles, equal_spacing, cw) in;                                         \n"
        "                                                                                  \n"
        "void main(void)                                                                   \n"
        "{                                                                                 \n"
        "    gl_Position = (gl_TessCoord.x * gl_in[0].gl_Position) +                       \n"
        "                  (gl_TessCoord.y * gl_in[1].gl_Position) +                       \n"
        "                  (gl_TessCoord.z * gl_in[2].gl_Position);                        \n"
        "}                                                                                 \n";


    QOpenGLShader* fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fs->compileSourceCode(fs_source);

    QOpenGLShader* vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vs->compileSourceCode(vs_source);

    QOpenGLShader* tcs = new QOpenGLShader(QOpenGLShader::TessellationControl, this);
    tcs->compileSourceCode(tcs_source);

    QOpenGLShader* tes = new QOpenGLShader(QOpenGLShader::TessellationEvaluation, this);
    tes->compileSourceCode(tes_source);

    program = new QOpenGLShaderProgram(this);
    program->addShader(vs);
    program->addShader(tcs);
    program->addShader(tes);
    program->addShader(fs);
    program->link();

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    QOpenGLVertexArrayObject* vao = new QOpenGLVertexArrayObject(this);
    vao->bind();
    program->bind();
}

void TessellatedTri::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawArrays(GL_PATCHES, 0, 3);
}

void TessellatedTri::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}
