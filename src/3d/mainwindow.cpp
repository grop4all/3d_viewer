#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    data_t data ;
    char str[20] = "../skull.obj";
    int a = parsline(str, &data);
    printf("%d", a);
    MyWidget* mywidget = new MyWidget();
    mywidget->initializeGL();
    mywidget->resize(200,200);
    mywidget->show();
    mywidget->paintGL(&data);

    ui->openGLWidget = mywidget;
    delete ui;
}

