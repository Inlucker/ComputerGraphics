#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //setStyleSheet("background-color:grey;");

    this->setFixedHeight(this->height());
    this->setFixedWidth(this->width());

    canvas = new Canvas();
    ui->gridLayout->addWidget(canvas);
    //canvas->show();
    //canvas->update();
}

MainWindow::~MainWindow()
{
    delete ui;
}

