#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QtOpenGL/qgl.h>
#include <QOpenGLFunctions>

class MyGLWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    MyGLWidget(QWidget *parent = nullptr);
    ~MyGLWidget();

protected:
    void initializeGL();
    void resizeGL(int, int);
    void paintGL();


signals:

};

#endif // MYGLWIDGET_H
