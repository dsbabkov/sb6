#ifndef FRAGCOLORFROMPOS_H
#define FRAGCOLORFROMPOS_H

#include <QGLWidget>
class QOpenGLShaderProgram;
class QOpenGLVertexArrayObject;
class FragColorFromPos : public QGLWidget
{
    Q_OBJECT
public:
    explicit FragColorFromPos(QWidget *parent = 0);

signals:

public slots:

private:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);
    void timerEvent(QTimerEvent *);

    QOpenGLShaderProgram* interpolateProgram,
                        * nonInterpolateProgram;
    bool interpolate;

};

#endif // FRAGCOLORFROMPOS_H
