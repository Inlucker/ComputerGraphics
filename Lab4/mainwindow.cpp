#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->method_comboBox->addItem("Каноническое уравнение");
    ui->method_comboBox->addItem("Параметрическое уравнение");
    ui->method_comboBox->addItem("Алгоритм Брезенхема");
    ui->method_comboBox->addItem("Алгоритм средней точки");
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
    delete canvas;
    delete ui;
}

void MainWindow::on_method_comboBox_activated(int index)
{
    switch (index)
    {
        case 0:
            canvas->method = CANON;
            break;
        case 1:
            canvas->method = PARAM;
            break;
        case 2:
            canvas->method = BREZENHAM;
            break;
        case 3:
            canvas->method = MIDPOINT;
            break;
        case 4:
            canvas->method = STANDART;
            break;
        default:
            //???
            break;
    }
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
            canvas->setPenColor(Qt::darkGreen);
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

void MainWindow::on_clean_Btn_clicked()
{
    canvas->clean();
}

void MainWindow::on_draw_circle_Btn_clicked()
{
    bool isXcFloat = false;
    float Xc = ui->X_center_Edit->text().toFloat(&isXcFloat);

    bool isYcFloat = false;
    float Yc = ui->Y_center_Edit->text().toFloat(&isYcFloat);

    bool isRFloat = false;
    float R = ui->R_Edit->text().toFloat(&isRFloat);


    if (isXcFloat)
        canvas->X_center = round(Xc);
    else
        QMessageBox::information(this, "Error", "X центра должен быть вещественным числом");

    if (isYcFloat)
        canvas->Y_center = round(Yc);
    else
        QMessageBox::information(this, "Error", "Y центра должен быть вещественным числом");

    if (isRFloat )
        canvas->Radius = round(R);
    else
        QMessageBox::information(this, "Error", "R - радиус должен быть положительным вещественным числом");


    if (isXcFloat && isYcFloat && isRFloat)
    {
        canvas->drawCircle();
        canvas->update();
    }
}

void MainWindow::on_draw_ellipse_Btn_clicked()
{
    bool isXcFloat = false;
    float Xc = ui->ellipse_X_center_Edit->text().toFloat(&isXcFloat);

    bool isYcFloat = false;
    float Yc = ui->ellipse_Y_center_Edit->text().toFloat(&isYcFloat);

    bool isAFloat = false;
    float a = ui->a_Edit_1->text().toFloat(&isAFloat);

    bool isBFloat = false;
    float b = ui->b_Edit_1->text().toFloat(&isBFloat);


    if (isXcFloat)
        canvas->X_center = round(Xc);
    else
        QMessageBox::information(this, "Error", "X центра должен быть вещественным числом");

    if (isYcFloat)
        canvas->Y_center = round(Yc);
    else
        QMessageBox::information(this, "Error", "Y центра должен быть вещественным числом");

    if (isAFloat)
        canvas->a = round(a);
    else
        QMessageBox::information(this, "Error", "a - должен быть положительным вещественным числом");

    if (isBFloat)
        canvas->b = round(b);
    else
        QMessageBox::information(this, "Error", "b - должен быть положительным вещественным числом");


    if (isXcFloat && isYcFloat && isAFloat && isBFloat)
    {
        canvas->drawEllipse();
        canvas->update();
    }
}
