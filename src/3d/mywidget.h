#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QOpenGLWidget>
#include <GL/gl.h>


class MyWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit MyWidget(QWidget *parent = nullptr);
    void initializeGL();
    void resizeGL(int h, int w);
    void paintGL();

signals:

};

#endif // MYWIDGET_H
