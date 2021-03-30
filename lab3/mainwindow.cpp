#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->method_comboBox->addItem("ЦДА");
    ui->method_comboBox->addItem("Брезенхем (int)");
    ui->method_comboBox->addItem("Брезенхем (float)");
    ui->method_comboBox->addItem("Брезенхем с устранением ступенчатости");
    ui->method_comboBox->addItem("Ву");
    ui->method_comboBox->addItem("QT");

    ui->penColor_comboBox->addItem("Чёрный");
    ui->penColor_comboBox->addItem("Красный");
    ui->penColor_comboBox->addItem("Зелёный");
    ui->penColor_comboBox->addItem("Синий");
    ui->penColor_comboBox->addItem("Белый");

    ui->backgroundColor_comboBox->addItem("Белый");
    ui->backgroundColor_comboBox->addItem("Красный");
    ui->backgroundColor_comboBox->addItem("Зелёный");
    ui->backgroundColor_comboBox->addItem("Синий");
    ui->backgroundColor_comboBox->addItem("Чёрный");

    this->setFixedHeight(this->height());
    this->setFixedWidth(this->width());

    canvas = new Canvas();
    ui->gridLayout->addWidget(canvas);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_draw_Btn_clicked()
{
    bool isXsFloat = false;
    float Xs = ui->X_start_Edit->text().toFloat(&isXsFloat);

    bool isYsFloat = false;
    float Ys = ui->Y_start_Edit->text().toFloat(&isYsFloat);

    bool isXeFloat = false;
    float Xe = ui->X_end_Edit->text().toFloat(&isXeFloat);

    bool isYeFloat = false;
    float Ye = ui->Y_end_Edit->text().toFloat(&isYeFloat);

    if (isXsFloat)
        canvas->X_start = Xs;
    else
        QMessageBox::information(this, "Error", "X начальный должен быть вещественным числом");

    if (isYsFloat)
        canvas->Y_start = Ys;
    else
        QMessageBox::information(this, "Error", "Y начальный должен быть вещественным числом");

    if (isXsFloat)
        canvas->X_end = Xe;
    else
        QMessageBox::information(this, "Error", "X конечный должен быть вещественным числом");

    if (isXsFloat)
        canvas->Y_end = Ye;
    else
        QMessageBox::information(this, "Error", "Y конечный должен быть вещественным числом");


    /*double dX = fabs(Xs - Xe), dY = abs(Ys - Ye);
    double l = fmax(dX, dY);
    dX = (Xe - Xs) / l;
    dY = (Ye - Ys) / l;
    //dX /= l;
    //dY /= l;
    double X = Xs, Y = Ys;

    while (fabs(X - Xe) > 1 || fabs(Y - Ye) > 1)
    {
        //painter.drawPoint(int(X), int(Y));
        QPoint p = QPoint(int(X), int(Y));
        canvas->draw_point(p);
        X = X + dX, Y += dY;
    }*/
    //canvas->setPenColor(Qt::green);
    canvas->draw();
    canvas->update();

}

void MainWindow::on_clean_Btn_clicked()
{
    canvas->clean();
}

void MainWindow::on_penColor_comboBox_activated(int index)
{
    switch (index)
    {
        case 0:
            canvas->setPenColor(Qt::black);
            break;
        case 1:
            canvas->setPenColor(Qt::red);
            break;
        case 2:
            canvas->setPenColor(Qt::green);
            break;
        case 3:
            canvas->setPenColor(Qt::blue);
            break;
        case 4:
            canvas->setPenColor(Qt::white);
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

void MainWindow::on_method_comboBox_activated(int index)
{
    switch (index)
    {
        case 0:
            canvas->method = DIG_DIF_ANALIZ;
            break;
        case 1:
            canvas->method = BREZENHAM_FLOAT;
            break;
        case 2:
            canvas->method = BREZENHAM_INT;
            break;
        case 3:
            canvas->method = BREZENHAM_STEP_REM;
            break;
        case 4:
            canvas->method = VU;
            break;
        case 5:
            canvas->method = STANDART;
            break;
        default:
            //???
            break;
    }

}
