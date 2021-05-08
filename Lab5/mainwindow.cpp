#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    ui->MainPenColor_comboBox->addItem("Красный");
    ui->MainPenColor_comboBox->addItem("Чёрный");
    ui->MainPenColor_comboBox->addItem("Зелёный");
    ui->MainPenColor_comboBox->addItem("Синий");
    ui->MainPenColor_comboBox->addItem("Белый");

    ui->SemiPenColor_comboBox->addItem("Чёрный");
    ui->SemiPenColor_comboBox->addItem("Красный");
    ui->SemiPenColor_comboBox->addItem("Зелёный");
    ui->SemiPenColor_comboBox->addItem("Синий");
    ui->SemiPenColor_comboBox->addItem("Белый");

    ui->backgroundColor_comboBox->addItem("Белый");
    ui->backgroundColor_comboBox->addItem("Красный");
    ui->backgroundColor_comboBox->addItem("Зелёный");
    ui->backgroundColor_comboBox->addItem("Синий");
    ui->backgroundColor_comboBox->addItem("Чёрный");

    canvas = new Canvas();
    ui->gridLayout_2->addWidget(canvas);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && this->canvas->rect().contains(event->pos()))
    {
        //cout << "Set" << endl;
        double x = event->position().x();
        double y = event->position().y();
        canvas->addPoint(x, y);
    }
}


void MainWindow::on_MainPenColor_comboBox_activated(int index)
{
    switch (index)
    {
        case 0:
            canvas->setMainPenColor(Qt::red);
            break;
        case 1:
            canvas->setMainPenColor(Qt::black);
            break;
        case 2:
            canvas->setMainPenColor(Qt::darkGreen);
            break;
        case 3:
            canvas->setMainPenColor(Qt::blue);
            break;
        case 4:
            canvas->setMainPenColor(Qt::white);
            break;
        default:
            //???
            break;
    }
}

void MainWindow::on_SemiPenColor_comboBox_activated(int index)
{
    switch (index)
    {
        case 0:
            canvas->setSemiPenColor(Qt::red);
            break;
        case 1:
            canvas->setSemiPenColor(Qt::black);
            break;
        case 2:
            canvas->setSemiPenColor(Qt::darkGreen);
            break;
        case 3:
            canvas->setSemiPenColor(Qt::blue);
            break;
        case 4:
            canvas->setSemiPenColor(Qt::white);
            break;
        default:
            //???
            break;
    }
}

void MainWindow::on_backgroundColor_comboBox_activated(int index)
{
    switch (index)
    {
        case 0:
            canvas->setStyleSheet("background-color:white;");
            break;
        case 1:
            canvas->setStyleSheet("background-color:red;");
            break;
        case 2:
            canvas->setStyleSheet("background-color:green;");
            break;
        case 3:
            canvas->setStyleSheet("background-color:blue;");
            break;
        case 4:
            canvas->setStyleSheet("background-color:black;");
            break;
        default:
            //???
            break;
    }
}

void MainWindow::on_lock_Btn_clicked()
{
    canvas->lock();
}


void MainWindow::on_Delay_on_radioButton_clicked()
{
    canvas->setDelay(true);
}

void MainWindow::on_Delay_off_radioButton_clicked()
{
    canvas->setDelay(false);
}

void MainWindow::on_clean_Btn_clicked()
{
    canvas->clean();
}
