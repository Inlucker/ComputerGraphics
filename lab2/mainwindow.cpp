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
    ui->coords_label->setText(tr("Текущее состояние:\nX: %1 Y: %2\nKx: %3 Ky: %4\nУгол: %5")
                              .arg(canvas->float_x[canvas->cur_id]).arg(canvas->float_y[canvas->cur_id]).arg(canvas->size_x[canvas->cur_id])
                              .arg(canvas->size_y[canvas->cur_id]).arg(canvas->angle[canvas->cur_id]));
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
        canvas->cur_id = 0;
        canvas->first_id = 0;
        canvas->float_x[canvas->cur_id] = x;
        canvas->float_y[canvas->cur_id] = y;
        canvas->x[canvas->cur_id] = canvas->float_x[canvas->cur_id];
        canvas->y[canvas->cur_id] = canvas->float_y[canvas->cur_id];
        canvas->size_x[canvas->cur_id] = 1;
        canvas->size_y[canvas->cur_id] = 1;
        canvas->angle[canvas->cur_id] = 0;
        canvas->rotate_center_x[canvas->cur_id] = 0;
        canvas->rotate_center_y[canvas->cur_id] = 0;
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
    ui->coords_label->setText(tr("Текущее состояние:\nX: %1 Y: %2\nKx: %3 Ky: %4\nУгол: %5")
                              .arg(canvas->float_x[canvas->cur_id]).arg(canvas->float_y[canvas->cur_id]).arg(canvas->size_x[canvas->cur_id])
                              .arg(canvas->size_y[canvas->cur_id]).arg(canvas->angle[canvas->cur_id]));
}

void MainWindow::on_move_btn_clicked()
{
    bool isXFloat = false;
    float x = ui->x_move->text().toFloat(&isXFloat);
    bool isYFloat = false;
    float y = ui->y_move->text().toFloat(&isYFloat);
    if (isXFloat && isYFloat)
    {
        int prev_id = canvas->cur_id;
        canvas->cur_id += 1;
        if (canvas->cur_id >= GAP)
        {
            canvas->cur_id = 0;
        }
        if (canvas->cur_id == canvas->first_id)
            canvas->first_id++;

        canvas->float_x[canvas->cur_id] = canvas->float_x[prev_id] + x;
        canvas->float_y[canvas->cur_id] = canvas->float_y[prev_id] + y;
        canvas->x[canvas->cur_id] = canvas->float_x[canvas->cur_id];
        canvas->y[canvas->cur_id] = canvas->float_y[canvas->cur_id];
        //Без изменений
        canvas->size_x[canvas->cur_id] = canvas->size_x[prev_id];
        canvas->size_y[canvas->cur_id] = canvas->size_y[prev_id];
        canvas->angle[canvas->cur_id] = canvas->angle[prev_id];
        canvas->rotate_center_x[canvas->cur_id] = canvas->rotate_center_x[prev_id];
        canvas->rotate_center_y[canvas->cur_id] = canvas->rotate_center_y[prev_id];
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
    ui->coords_label->setText(tr("Текущее состояние:\nX: %1 Y: %2\nKx: %3 Ky: %4\nУгол: %5")
                              .arg(canvas->float_x[canvas->cur_id]).arg(canvas->float_y[canvas->cur_id]).arg(canvas->size_x[canvas->cur_id])
                              .arg(canvas->size_y[canvas->cur_id]).arg(canvas->angle[canvas->cur_id]));
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
        int prev_id = canvas->cur_id;
        canvas->cur_id += 1;
        if (canvas->cur_id >= GAP)
        {
            canvas->cur_id = 0;
        }
        if (canvas->cur_id == canvas->first_id)
            canvas->first_id++;

        canvas->float_x[canvas->cur_id] = kx * canvas->float_x[prev_id] + xc * (1 - kx);
        canvas->float_y[canvas->cur_id] = ky * canvas->float_y[prev_id] + yc * (1 - ky);
        canvas->x[canvas->cur_id] = canvas->float_x[canvas->cur_id];
        canvas->y[canvas->cur_id] = canvas->float_y[canvas->cur_id];
        canvas->size_x[canvas->cur_id] = canvas->size_x[prev_id] * kx;
        canvas->size_y[canvas->cur_id] = canvas->size_y[prev_id] * ky;
        //Без изменений
        canvas->angle[canvas->cur_id] = canvas->angle[prev_id];
        canvas->rotate_center_x[canvas->cur_id] = canvas->rotate_center_x[prev_id];
        canvas->rotate_center_y[canvas->cur_id] = canvas->rotate_center_y[prev_id];
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
    ui->coords_label->setText(tr("Текущее состояние:\nX: %1 Y: %2\nKx: %3 Ky: %4\nУгол: %5")
                              .arg(canvas->float_x[canvas->cur_id]).arg(canvas->float_y[canvas->cur_id]).arg(canvas->size_x[canvas->cur_id])
                              .arg(canvas->size_y[canvas->cur_id]).arg(canvas->angle[canvas->cur_id]));
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
        int prev_id = canvas->cur_id;
        canvas->cur_id += 1;
        if (canvas->cur_id >= GAP)
        {
            canvas->cur_id = 0;
        }
        if (canvas->cur_id == canvas->first_id)
            canvas->first_id++;

        canvas->angle[canvas->cur_id] = canvas->angle[prev_id] + angle;
        if (abs(canvas->angle[canvas->cur_id] - 360) <= EPS || canvas->angle[canvas->cur_id] > 360)
        {
            //cout << int(canvas->angle / 360) * 360 << endl;
            canvas->angle[canvas->cur_id] -= int(canvas->angle[canvas->cur_id] / 360) * 360;
        }
        //cout << abs(canvas->angle - int(canvas->angle / 360) * 360) << " " << EPS << endl;
        if (abs(canvas->angle[canvas->cur_id] - int(canvas->angle[canvas->cur_id] / 360) * 360) <= EPS)
            canvas->angle[canvas->cur_id] = 0;
        canvas->rotate_center_x[canvas->cur_id] = xc;
        canvas->rotate_center_y[canvas->cur_id] = yc;
        //Без изменений
        canvas->float_x[canvas->cur_id] = canvas->float_x[prev_id];
        canvas->float_y[canvas->cur_id] = canvas->float_y[prev_id];
        canvas->x[canvas->cur_id] = canvas->float_x[canvas->cur_id];
        canvas->y[canvas->cur_id] = canvas->float_y[canvas->cur_id];
        canvas->size_x[canvas->cur_id] = canvas->size_x[prev_id];
        canvas->size_y[canvas->cur_id] = canvas->size_y[prev_id];
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
    ui->coords_label->setText(tr("Текущее состояние:\nX: %1 Y: %2\nKx: %3 Ky: %4\nУгол: %5")
                              .arg(canvas->float_x[canvas->cur_id]).arg(canvas->float_y[canvas->cur_id]).arg(canvas->size_x[canvas->cur_id])
                              .arg(canvas->size_y[canvas->cur_id]).arg(canvas->angle[canvas->cur_id]));
}

void MainWindow::on_pushButton_clicked()
{
    if (canvas->cur_id == canvas->first_id)
    {
        QMessageBox::information(this, "Error", "Действий не найдено");
    }
    else
    {
        canvas->cur_id -= 1;
        if (canvas->cur_id < 0)
            canvas->cur_id = GAP;
        canvas->update();
    }
}
