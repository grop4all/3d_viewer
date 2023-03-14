#include "myglwidget.h"

MyGLWidget::MyGLWidget (QWidget *parent)
    : QOpenGLWidget(parent)
{
}



void initiaseGL() {

    glClearColor(0.0f,0.0f,0.0f,1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

}
void resizeGL() {
    float aspect = w / (float)h;
    m_pro
}
void paintGL() {

}
