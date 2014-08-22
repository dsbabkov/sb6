#ifndef SIMPLECLEAR_H
#define SIMPLECLEAR_H

#include <QGLWidget>

class SimpleClear : public QGLWidget
{
    Q_OBJECT
public:
    explicit SimpleClear(QWidget *parent = 0);

signals:

public slots:
private:
    void initializeGL();
    void paintGL();
};

#endif // SIMPLECLEAR_H
