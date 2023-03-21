#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    setlocale(LC_NUMERIC, "C");
    MainWindow w;
    w.show();
    data_t data ;
    char str[40] = "../test_sample/test.obj";
    parsline(str, &data);
    MyWidget* mywidget = new MyWidget();
    mywidget->initializeGL();
    mywidget->resize(200,200);
    mywidget->paintGL(&data);
    mywidget->show();

    return a.exec();
}
