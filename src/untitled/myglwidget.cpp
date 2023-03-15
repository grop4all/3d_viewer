#include "myglwidget.h"

MyGLWidget::MyGLWidget (QWidget *parent)
    : QOpenGLWidget(parent)
{
}



void initiaseGL() {

    glClearColor(0.0f,0.0f,0.0f,1.0f);
    glEnable(GL_DEPTH_TEST);

}
void resizeGL(int w, int h) {
}


void paintGL() {
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_DOUBLE, 0, vertex_array);

    glDrawElements(GL_LINES, edges_counter, GL_UNSIGNED_INT, indexes_array)
    glDisableClientState(GL_VERTEX_ARRAY);

}
