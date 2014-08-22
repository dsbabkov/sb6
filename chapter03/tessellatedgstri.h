#ifndef TESSELLATEDGSTRI_H
#define TESSELLATEDGSTRI_H

#include <QGLWidget>
class QOpenGLShaderProgram;
class QOpenGLVertexArrayObject;
class TessellatedGsTri : public QGLWidget
{
    Q_OBJECT
public:
    explicit TessellatedGsTri(QWidget *parent = 0);

signals:

public slots:

private:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

    QOpenGLShaderProgram* program;

};

#endif // TESSELLATEDGSTRI_H
