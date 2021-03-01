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

    ui->x_start->setText("0");
    ui->y_start->setText("0");
    ui->x_move->setText("0");
    ui->y_move->setText("0");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_create_btn_clicked()
{
    bool isXFloat = false;
    float x = ui->x_start->text().toFloat(&isXFloat);
    bool isYFloat = false;
    float y = ui->y_start->text().toFloat(&isYFloat);
    if (isXFloat && isYFloat)
    {
        canvas->float_x = x;
        canvas->float_y = y * -1;
        canvas->x = canvas->float_x;
        canvas->y = canvas->float_y;
        canvas->update();
    }
    else if (!isXFloat && !isYFloat)
    {
        QMessageBox::information(this, "Error", "X и Y должны быть вещественными числами");
    }
    else if (!isXFloat)
    {
        QMessageBox::information(this, "Error", "X должен быть вещественным числом");
    }
    else if (!isYFloat)
    {
        QMessageBox::information(this, "Error", "Y должен быть вещественным числом");
    }
    ui->coords_label->setText(tr("%1 %2").arg(canvas->float_x).arg(canvas->float_y));
}

void MainWindow::on_move_btn_clicked()
{
    bool isXFloat = false;
    float x = ui->x_move->text().toFloat(&isXFloat);
    bool isYFloat = false;
    float y = ui->y_move->text().toFloat(&isYFloat);
    if (isXFloat && isYFloat)
    {
        canvas->float_x += x;
        canvas->float_y += y * -1;
        canvas->x = canvas->float_x;
        canvas->y = canvas->float_y;
        canvas->update();
    }
    else if (!isXFloat && !isYFloat)
    {
        QMessageBox::information(this, "Error", "X и Y должны быть вещественными числами");
    }
    else if (!isXFloat)
    {
        QMessageBox::information(this, "Error", "X должен быть вещественным числом");
    }
    else if (!isYFloat)
    {
        QMessageBox::information(this, "Error", "Y должен быть вещественным числом");
    }
    ui->coords_label->setText(tr("%1 %2").arg(canvas->float_x).arg(canvas->float_y));
}
