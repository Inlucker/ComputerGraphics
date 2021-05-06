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


    circleTimeGraphs = new CircleTimeGraphs();
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

    if (isRFloat && R > 0)
        canvas->Radius = round(R);
    else
        QMessageBox::information(this, "Error", "R - радиус должен быть положительным вещественным числом");


    if (isXcFloat && isYcFloat && isRFloat && R > 0)
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

    if (isAFloat && a > 0)
        canvas->a = round(a);
    else
        QMessageBox::information(this, "Error", "a - должен быть положительным вещественным числом");

    if (isBFloat && b > 0)
        canvas->b = round(b);
    else
        QMessageBox::information(this, "Error", "b - должен быть положительным вещественным числом");


    if (isXcFloat && isYcFloat && isAFloat && a > 0 && isBFloat && b > 0)
    {
        canvas->drawEllipse();
        canvas->update();
    }
}

void MainWindow::on_pushButton_clicked()
{
    bool isXcFloat = false;
    float Xc = ui->X_center_Edit_2->text().toFloat(&isXcFloat);

    bool isYcFloat = false;
    float Yc = ui->Y_center_Edit_2->text().toFloat(&isYcFloat);

    bool isR1Float = false;
    float R1 = ui->R1_Edit->text().toFloat(&isR1Float);

    bool isR2Float = false;
    float R2 = ui->R2_Edit->text().toFloat(&isR2Float);

    bool isCircleNumberInt = false;
    int CircleN = ui->circle_number_Edit->text().toInt(&isCircleNumberInt);

    if (isXcFloat)
        canvas->X_center = round(Xc);
    else
        QMessageBox::information(this, "Error", "X центра должен быть вещественным числом");

    if (isYcFloat)
        canvas->Y_center = round(Yc);
    else
        QMessageBox::information(this, "Error", "Y центра должен быть вещественным числом");

    if (isR1Float && R1 > 0)
        canvas->RadiusStart = round(R1);
    else
        QMessageBox::information(this, "Error", "Rн - начальный радиус должен быть положительным вещественным числом");

    if (isR2Float && R2 > 0)
        canvas->RadiusEnd = round(R2);
    else
        QMessageBox::information(this, "Error", "Rк - конечный радиус должен быть положительным вещественным числом");


    if (isCircleNumberInt && CircleN > 0)
        canvas->FiguresNumber = round(CircleN);
    else
        QMessageBox::information(this, "Error", "Кол-во окружностей должно быть натуральным числом");


    if (isXcFloat && isYcFloat && isR1Float && R1 > 0 && isR2Float && R2 > 0 && isCircleNumberInt && CircleN > 0)
    {
        canvas->drawCircleSpectre();
        canvas->update();
    }
}

void MainWindow::on_pushButton_2_clicked()
{

    bool isXcFloat = false;
    float Xc = ui->ellipse_spectre_X_center_Edit->text().toFloat(&isXcFloat);

    bool isYcFloat = false;
    float Yc = ui->ellipse_spectre_Y_center_Edit->text().toFloat(&isYcFloat);

    bool isAFloat = false;
    float A = ui->a_Edit_2->text().toFloat(&isAFloat);

    bool isBFloat = false;
    float B = ui->b_Edit_2->text().toFloat(&isBFloat);

    bool isStepFloat = false;
    float Step = ui->ellipse_spectre_step_Edit->text().toFloat(&isStepFloat);

    bool isCircleNumberInt = false;
    int EllipseN = ui->ellipse_number_Edit->text().toInt(&isCircleNumberInt);

    if (isXcFloat)
        canvas->X_center = round(Xc);
    else
        QMessageBox::information(this, "Error", "X центра должен быть вещественным числом");

    if (isYcFloat)
        canvas->Y_center = round(Yc);
    else
        QMessageBox::information(this, "Error", "Y центра должен быть вещественным числом");

    if (isAFloat && A > 0)
        canvas->a_start = round(A);
    else
        QMessageBox::information(this, "Error", "a начальный - параметр должен быть положительным вещественным числом");

    if (isBFloat && B > 0)
        canvas->b_start = round(B);
    else
        QMessageBox::information(this, "Error", "b начальный - параметр должен быть положительным вещественным числом");


    if (isStepFloat && Step > 0)
    {
        if (ui->a_change->isChecked())
        {
            canvas->stepA = Step;
            canvas->stepB = 0;
        }
        else
        {
            canvas->stepA = 0;
            canvas->stepB = Step;
        }
    }
    else
        QMessageBox::information(this, "Error", "Шаг должен быть положительным вещественным числом");

    if (isCircleNumberInt && EllipseN > 0)
        canvas->FiguresNumber = round(EllipseN);
    else
        QMessageBox::information(this, "Error", "Кол-во окружностей должно быть натуральным числом");


    if (isXcFloat && isYcFloat && isAFloat && A > 0 && isBFloat && B > 0 && isCircleNumberInt && EllipseN > 0)
    {
        canvas->drawEllipseSpectre();
        canvas->update();
    }
}

void MainWindow::on_set_balck_Btn_clicked()
{
    canvas->setPenColor(Qt::black);
    ui->penColor_comboBox->setCurrentIndex(0);
}

void MainWindow::on_set_white_Btn_clicked()
{
    canvas->setPenColor(Qt::white);
    ui->penColor_comboBox->setCurrentIndex(4);
}

#include <iostream>

using namespace std;

void MainWindow::on_show_graphs_Btn_clicked()
{

    //bool isLengthFloat = false;
    //double Radius = ui->Len_Edit->text().toFloat(&isLengthFloat);

    //if (isLengthFloat)
    if (true)
    {
        int n = 10;
        //double func[5][n];
        double **func = new double *[5];
        for (int i = 0; i < 5; i++)
          func[i] = new double [n];

        //double Radius = 100;
        for (int i = 0; i < n; i++)
        {
            func[0][i] = canvas->getCircleTime(I_RADIUS, CANON);
            func[1][i] = canvas->getCircleTime(I_RADIUS, PARAM);
            func[2][i] = canvas->getCircleTime(I_RADIUS, BREZENHAM);
            func[3][i] = canvas->getCircleTime(I_RADIUS, MIDPOINT);
            func[4][i] = canvas->getCircleTime(I_RADIUS, STANDART);
        }
        for (int j = 0; j < 5; j++)
        {
            cout << j << endl;
            for (int i = 0; i < n; i++)
            {
                cout << (i+1)*10 << "; " << func[j][i] << endl;
            }
        }

        circleTimeGraphs->makePlot(n, func, true);

        for (int i = 0; i < 5; i++)
          delete []func[i];
        delete []func;

        circleTimeGraphs->show();
        circleTimeGraphs->activateWindow();
    }
    else
        QMessageBox::information(this, "Error", "Длина отрезка должна быть вещественным числом");

    /*circleTimeGraphs->makePlot();
    circleTimeGraphs->show();
    circleTimeGraphs->activateWindow();*/
}

void MainWindow::on_stage_Btn_clicked()
{
    if (true)
    {
        int n = 10;
        //double func[5][n];
        double **func = new double *[5];
        for (int i = 0; i < 5; i++)
          func[i] = new double [n];

        //double Radius = 100;
        for (int i = 0; i < n; i++)
        {
            func[0][i] = canvas->getEllipseTime(I_RADIUS, I_RADIUS, CANON);
            func[1][i] = canvas->getEllipseTime(I_RADIUS, I_RADIUS, PARAM);
            func[2][i] = canvas->getEllipseTime(I_RADIUS, I_RADIUS, BREZENHAM);
            func[3][i] = canvas->getEllipseTime(I_RADIUS, I_RADIUS, MIDPOINT);
            func[4][i] = canvas->getEllipseTime(I_RADIUS, I_RADIUS, STANDART);
        }

        circleTimeGraphs->makePlot(n, func, false);

        for (int i = 0; i < 5; i++)
          delete []func[i];
        delete []func;

        circleTimeGraphs->show();
        circleTimeGraphs->activateWindow();
    }
    else
        QMessageBox::information(this, "Error", "Длина отрезка должна быть вещественным числом");
}
