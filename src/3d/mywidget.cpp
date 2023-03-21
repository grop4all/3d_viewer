#include "mywidget.h"




MyWidget::MyWidget(QWidget *parent)
    : QOpenGLWidget{parent}
{

}


void MyWidget::initializeGL(){

}

void MyWidget::resizeGL(int h, int w) {

}

void MyWidget::paintGL(data_t* data){
     glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for(int i = 1; i < data->count_of_facets; ++i){
        for(int j = 1; j < data->polygons[i].numbers_of_vertexes_in_facets; ++j) {
            glBegin(GL_LINE_LOOP);
            glVertex3d(data->matrix_3d.matrix[data->polygons[i].vertexes[j]][0],
                    data->matrix_3d.matrix[data->polygons[i].vertexes[j]][1],
                    data->matrix_3d.matrix[data->polygons[i].vertexes[j]][2]);
        }
    glEnd();
    }
}

