#ifndef SINGLEPOINT_H
#define SINGLEPOINT_H

#include <QGLWidget>
class QGLShaderProgram;
class QOpenGLVertexArrayObject;
class SinglePoint : public QGLWidget
{
    Q_OBJECT
public:
    explicit SinglePoint(QWidget *parent = 0);

signals:

public slots:

private:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

    QGLShaderProgram* program;
//    QOpenGLVertexArrayObject* vao;

};

#endif // SINGLEPOINT_H
