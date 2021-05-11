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

/*void MainWindow::mousePressEvent(QMouseEvent *event)
{
    cout << canvas->geometry().x() << endl;
    if (event->button() == Qt::LeftButton && this->canvas->rect().contains(event->pos()))
    {
        double x = canvas->prev_x;
        double y = canvas->prev_y;
        if (event->modifiers() == Qt::ALT && !canvas->firstPointCheck())
        {
            x = event->position().x() - canvas->x();
            if (event->position().y() < y)
                y = y - (x - canvas->prev_x) - canvas->y();
            else
                y = y + (x - canvas->prev_x);
            cout << "HERE" << endl;
        }
        else if (event->modifiers() == Qt::CTRL && !canvas->firstPointCheck())
        {
            x = event->position().x() - canvas->x();
        }
        else if (event->modifiers() == Qt::SHIFT && !canvas->firstPointCheck())
        {
            y = event->position().y() - canvas->y();
        }
        else
        {
            x = event->position().x() - canvas->x();
            y = event->position().y() - canvas->y();
        }

        canvas->addPoint(x, y);
    }
}*/


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
    canvas->clean();
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
    canvas->clean();
}

void MainWindow::on_backgroundColor_comboBox_activated(int index)
{
    switch (index)
    {
        case 0:
            canvas->setStyleSheet("background-color:white;");
            canvas->setBackgroundColor(Qt::white);
            break;
        case 1:
            canvas->setStyleSheet("background-color:red;");
            canvas->setBackgroundColor(Qt::red);
            break;
        case 2:
            canvas->setStyleSheet("background-color:green;");
            canvas->setBackgroundColor(Qt::darkGreen);
            break;
        case 3:
            canvas->setStyleSheet("background-color:blue;");
            canvas->setBackgroundColor(Qt::blue);
            break;
        case 4:
            canvas->setStyleSheet("background-color:black;");
            canvas->setBackgroundColor(Qt::black);
            break;
        default:
            //???
            break;
    }
    canvas->clean();
}

void MainWindow::on_add_point_Btn_clicked()
{
    bool isXFloat = false;
    float X = ui->X_Edit->text().toFloat(&isXFloat);

    bool isYFloat = false;
    float Y = ui->Y_Edit->text().toFloat(&isYFloat);

    if (!isXFloat)
        QMessageBox::information(this, "Error", "X должен быть вещественным числом");

    if (!isYFloat)
        QMessageBox::information(this, "Error", "Y должен быть вещественным числом");

    if (isXFloat && isYFloat)
        canvas->addPoint(round(X), round(Y));
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

void MainWindow::on_fill_Btn_clicked()
{
    if (!canvas->locked())
    {
        QMessageBox::information(this, "Error", "Фигура не замкнута. Пожалуйста, замкните фигуру.");
        return;
    }

    if (canvas->getEdgesNumber() <= 2)
    {
        QMessageBox::information(this, "Error", "Недостаточно ребер.");
        return;
    }

    bool isDelayFloat = false;
    float delay = ui->delay_Edit->text().toFloat(&isDelayFloat);

    delay = round(delay);

    if (!isDelayFloat || delay > 50 || delay < 0)
        QMessageBox::information(this, "Error", "Задержка должна быть неотрицательным вещественным числом не больше 50");

    if (isDelayFloat && delay <= 50 && delay >= 0)
        canvas->fill(delay);
}

/*#define X_START 50
#define Y_START 50
#define FIG_WIDTH 100
#define FIG_HEIGHT 200*/

#define X_START 10
#define Y_START 10
#define FIG_WIDTH 30
#define FIG_HEIGHT 30

void MainWindow::on_pushButton_clicked()
{
    canvas->addPoint(X_START, Y_START);
    canvas->addPoint(X_START, Y_START + 2 * FIG_HEIGHT);
    canvas->addPoint(X_START + FIG_WIDTH, Y_START + FIG_HEIGHT);
    canvas->addPoint(X_START + 2 * FIG_WIDTH, Y_START + 2 * FIG_HEIGHT);
    canvas->addPoint(X_START + 2 * FIG_WIDTH, Y_START);
    canvas->lock();
}

void MainWindow::on_get_time_Btn_clicked()
{
    auto start = chrono::high_resolution_clock::now();
    canvas->setDelay(false);
    on_fill_Btn_clicked();
    if (ui->Delay_on_radioButton->isChecked())
        canvas->setDelay(true);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> dur = end - start;
    QMessageBox::information(this, "Время закраски", QString("Время закраски = %1").arg(dur.count()));
}
