#ifndef MOVINGTRI_H
#define MOVINGTRI_H

#include <QGLWidget>

class QTime;
class QTimerEvent;
class QVector4D;
class QGLShaderProgram;
class QOpenGLVertexArrayObject;
class MovingTri : public QGLWidget
{
    Q_OBJECT
public:
    explicit MovingTri(QWidget *parent = 0);
    ~MovingTri();
signals:

public slots:

private:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);
    void timerEvent(QTimerEvent *);

    QGLShaderProgram* program;
    QTime* time;
};

#endif // MOVINGTRI_H
