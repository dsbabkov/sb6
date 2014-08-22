#ifndef TESSELLATEDTRI_H
#define TESSELLATEDTRI_H

#include <QGLWidget>
class QOpenGLShaderProgram;
class QOpenGLVertexArrayObject;
class TessellatedTri : public QGLWidget
{
    Q_OBJECT
public:
    explicit TessellatedTri(QWidget *parent = 0);

signals:

public slots:

private:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

    QOpenGLShaderProgram* program;

};

#endif // TESSELLATEDTRI_H
