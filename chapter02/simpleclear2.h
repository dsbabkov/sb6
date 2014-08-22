#ifndef SIMPLECLEAR2_H
#define SIMPLECLEAR2_H

#include <QGLWidget>


class QTimerEvent;
class QTime;

class SimpleClear2 : public QGLWidget
{
    Q_OBJECT
public:
    explicit SimpleClear2(QWidget *parent = 0);
    ~SimpleClear2();

signals:

public slots:
private:
    void initializeGL();
    void paintGL();
    void timerEvent(QTimerEvent *);
    GLclampf r, g;
    QTime* time;
};

#endif // SIMPLECLEAR2_H
