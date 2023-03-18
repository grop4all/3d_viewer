#include "mywidget.h"



MyWidget::MyWidget(QWidget *parent)
    : QOpenGLWidget{parent}
{

}


void MyWidget::initializeGL(){
    glEnable(GL_DEPTH_TEST);
}

void MyWidget::resizeGL(int h, int w) {

}

void MyWidget::paintGL(){

}

