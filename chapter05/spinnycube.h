#ifndef SPINNYCUBE_H
#define SPINNYCUBE_H

#include <QGLWidget>

class QOpenGLShaderProgram;
class QOpenGLVertexArrayObject;
class QMatrix4x4;
class QTimerEvent;
class QTime;

class SpinnyCube : public QGLWidget
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
    QTime* time;

    bool many;

};

#endif // SPINNYCUBE_H
