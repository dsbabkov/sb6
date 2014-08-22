#ifndef SINGLETRI_H
#define SINGLETRI_H

#include <QGLWidget>
class QOpenGLShaderProgram;
class QOpenGLVertexArrayObject;
class SingleTri : public QGLWidget
{
    Q_OBJECT
public:
    explicit SingleTri(QWidget *parent = 0);

signals:

public slots:

private:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

    QOpenGLShaderProgram* program;

};

#endif // SINGLETRI_H
