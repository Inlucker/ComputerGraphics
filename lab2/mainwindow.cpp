#include "mainwindow.h"
#include "ui_mainwindow.h"

#define EPS 1e-3

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
    ui->x_size_center->setText("0");
    ui->y_size_center->setText("0");
    ui->x_size->setText("1.2");
    ui->y_size->setText("1.0");

    ui->x_rotate_center->setText("0");
    ui->y_rotate_center->setText("0");
    ui->rotate_angle->setText("90");

    //ui->coords_label->setText(tr("X: %1 Y: %2\nKx: %3 Ky: %4").arg(canvas->float_x).arg(canvas->float_y * (-1)).arg(canvas->size_x).arg(canvas->size_y));
    ui->coords_label->setText(tr("X: %1 Y: %2\nKx: %3 Ky: %4\nAngle: %5").arg(canvas->float_x).arg(canvas->float_y).arg(canvas->size_x).arg(canvas->size_y).arg(canvas->angle));
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
        //canvas->float_y = y * (-1);
        canvas->float_y = y;
        canvas->x = canvas->float_x;
        canvas->y = canvas->float_y;
        canvas->size_x = 1;
        canvas->size_y = 1;
        canvas->angle = 0;
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
    //ui->coords_label->setText(tr("X: %1 Y: %2\nKx: %3 Ky: %4").arg(canvas->float_x).arg(canvas->float_y * (-1)).arg(canvas->size_x).arg(canvas->size_y));
    ui->coords_label->setText(tr("X: %1 Y: %2\nKx: %3 Ky: %4\nAngle: %5").arg(canvas->float_x).arg(canvas->float_y).arg(canvas->size_x).arg(canvas->size_y).arg(canvas->angle));
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
        //canvas->float_y += y * (-1);
        canvas->float_y += y;
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
    //ui->coords_label->setText(tr("X: %1 Y: %2\nKx: %3 Ky: %4").arg(canvas->float_x).arg(canvas->float_y * (-1)).arg(canvas->size_x).arg(canvas->size_y));
    ui->coords_label->setText(tr("X: %1 Y: %2\nKx: %3 Ky: %4").arg(canvas->float_x).arg(canvas->float_y).arg(canvas->size_x).arg(canvas->size_y));
}

void MainWindow::on_change_size_btn_clicked()
{
    bool isXcFloat = false;
    float xc = ui->x_size_center->text().toFloat(&isXcFloat);
    bool isYcFloat = false;
    float yc = ui->y_size_center->text().toFloat(&isYcFloat);

    bool isKxFloat = false;
    float kx = ui->x_size->text().toFloat(&isKxFloat);
    bool isKyFloat = false;
    float ky = ui->y_size->text().toFloat(&isKyFloat);
    if (isXcFloat && isYcFloat &&isKxFloat && isKyFloat)
    {
        canvas->float_x = kx * canvas->float_x + xc * (1 - kx);
        //canvas->float_y = (ky * canvas->float_y * (-1) + yc * (1 - ky)) * (-1);
        canvas->float_y = ky * canvas->float_y + yc * (1 - ky);
        canvas->x = canvas->float_x;
        canvas->y = canvas->float_y;
        canvas->size_x *= kx;
        canvas->size_y *= ky;
        canvas->update();
    }
    else if (!isKxFloat || !isKyFloat|| isXcFloat || isYcFloat)
    {
        QMessageBox::information(this, "Error", "Xc, Yc, Kx и Ky должны быть вещественными числами");
    }
    /*else if (!isKxFloat)
    {
        QMessageBox::information(this, "Error", "Kx должен быть вещественным числом");
    }
    else if (!isKyFloat)
    {
        QMessageBox::information(this, "Error", "Ky должен быть вещественным числом");
    }*/
    //ui->coords_label->setText(tr("X: %1 Y: %2\nKx: %3 Ky: %4").arg(canvas->float_x).arg(canvas->float_y * (-1)).arg(canvas->size_x).arg(canvas->size_y));
    ui->coords_label->setText(tr("X: %1 Y: %2\nKx: %3 Ky: %4\nAngle: %5").arg(canvas->float_x).arg(canvas->float_y).arg(canvas->size_x).arg(canvas->size_y).arg(canvas->angle));
}

void MainWindow::on_rotate_btn_clicked()
{
    bool isXcFloat = false;
    float xc = ui->x_rotate_center->text().toFloat(&isXcFloat);
    bool isYcFloat = false;
    float yc = ui->y_rotate_center->text().toFloat(&isYcFloat);

    bool isAngleFloat = false;
    float angle = ui->rotate_angle->text().toFloat(&isAngleFloat);
    if (isXcFloat && isYcFloat && isAngleFloat)
    {
        canvas->angle += angle;
        if (abs(canvas->angle - 360) <= EPS || canvas->angle > 360)
        {
            //cout << int(canvas->angle / 360) * 360 << endl;
            canvas->angle -= int(canvas->angle / 360) * 360;
        }
        //cout << abs(canvas->angle - int(canvas->angle / 360) * 360) << " " << EPS << endl;
        if (abs(canvas->angle - int(canvas->angle / 360) * 360) <= EPS)
            canvas->angle = 0;
        canvas->rotate_center_x = xc;
        canvas->rotate_center_y = yc;
        canvas->update();
    }
    if (!isXcFloat || !isYcFloat)
    {
        QMessageBox::information(this, "Error", "Xc и Yc должны быть вещественными числами");
    }
    if (!isAngleFloat)
    {
        QMessageBox::information(this, "Error", "Угол φ должен быть вещественным числом");
    }
    ui->coords_label->setText(tr("X: %1 Y: %2\nKx: %3 Ky: %4\nAngle: %5").arg(canvas->float_x).arg(canvas->float_y).arg(canvas->size_x).arg(canvas->size_y).arg(canvas->angle));
}
