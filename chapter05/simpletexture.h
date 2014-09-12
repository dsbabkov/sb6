#ifndef SIMPLETEXTURE_H
#define SIMPLETEXTURE_H

#include <QGLWidget>

class QOpenGLShaderProgram;
class QOpenGLVertexArrayObject;
class QOpenGLTexture;

class SimpleTexture : public QGLWidget
{
    Q_OBJECT
public:
    explicit SimpleTexture(QWidget *parent = 0);
//    ~SimpleTexture();

signals:

public slots:

private:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

    QOpenGLShaderProgram* program;
    QOpenGLTexture* texture;
void generate_texture(float * data, int width, int height)
{
    int x, y;

    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width; x++)
        {
            data[(y * width + x) * 4 + 0] = (float)((x & y) & 0xFF) / 255.0f;
            data[(y * width + x) * 4 + 1] = (float)((x | y) & 0xFF) / 255.0f;
            data[(y * width + x) * 4 + 2] = (float)((x ^ y) & 0xFF) / 255.0f;
            data[(y * width + x) * 4 + 3] = 1.0f;
        }
    }
}

};

#endif // SIMPLETEXTURE_H
