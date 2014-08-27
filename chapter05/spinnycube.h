#ifndef SPINNYCUBE_H
#define SPINNYCUBE_H

#include <QGLWidget>
#include <QOpenGLFunctions_4_3_Core>

class QOpenGLShaderProgram;
class QOpenGLVertexArrayObject;
class QMatrix4x4;
class QTimerEvent;
class QTime;

class SpinnyCube : public QGLWidget, protected QOpenGLFunctions_4_3_Core
{
    Q_OBJECT
public:
    explicit SpinnyCube(QWidget *parent = 0);
    ~SpinnyCube();

signals:

public slots:

private:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

    void timerEvent(QTimerEvent *);

    int mv_location,
        proj_location;

    QOpenGLShaderProgram* program;
    QMatrix4x4* proj_matrix;
//    GLuint          program;
    GLuint          vao;
    GLuint          buffer;
//    GLint           mv_location;
//    GLint           proj_location;

    float           aspect;

    QTime* time;


};

#endif // SPINNYCUBE_H
