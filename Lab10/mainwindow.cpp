#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setFixedHeight(height());
    setFixedWidth(width());

    ui->SemiPenColor_comboBox->addItem("Чёрный");
    ui->SemiPenColor_comboBox->addItem("Красный");
    ui->SemiPenColor_comboBox->addItem("Зелёный");
    ui->SemiPenColor_comboBox->addItem("Синий");

    ui->backgroundColor_comboBox->addItem("Белый");
    ui->backgroundColor_comboBox->addItem("Синий");
    ui->backgroundColor_comboBox->addItem("Красный");
    ui->backgroundColor_comboBox->addItem("Зелёный");
    ui->backgroundColor_comboBox->addItem("Чёрный");

    ui->comboBox->setItemData(0, Qt::AlignCenter, Qt::TextAlignmentRole);
    ui->comboBox->setItemData(1, Qt::AlignCenter, Qt::TextAlignmentRole);
    ui->comboBox->setItemData(2, Qt::AlignCenter, Qt::TextAlignmentRole);
    ui->comboBox->setItemData(3, Qt::AlignCenter, Qt::TextAlignmentRole);
    ui->comboBox->setItemData(4, Qt::AlignCenter, Qt::TextAlignmentRole);

    canvas = new Canvas();
    ui->gridLayout_2->addWidget(canvas);

    cur_func = func1;

    LMB_is_pressed = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        LMB_is_pressed = false;
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && !LMB_is_pressed && this->canvas->rect().contains(event->pos()))
    {
        previous_x = event->position().x();
        previous_y = event->position().y();
        LMB_is_pressed = true;
    }
}

#define ROTATE_SPEED 10

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (LMB_is_pressed)
    {
        double dx = double(previous_x - event->position().x()) / ROTATE_SPEED;
        double dy = double(-previous_y + event->position().y()) / ROTATE_SPEED;

        canvas->rotate_x(dy);
        canvas->rotate_y(dx);
        canvas->draw(cur_func, ui->x_min->text().toDouble(), ui->x_max->text().toDouble(),
                        ui->x_step->text().toDouble(), ui->z_min->text().toDouble(),
                        ui->z_max->text().toDouble(), ui->z_step->text().toDouble());

        //canvas->update();
        previous_x = event->position().x();
        previous_y = event->position().y();
    }
}

#define SCALE_SPEED 10

void MainWindow::wheelEvent(QWheelEvent *event)
{
    if (this->canvas->rect().contains(int(event->position().x()), int(event->position().y())))
    {
        QPoint numDegrees = event->angleDelta() / 120;
        double ky = 1 + double(numDegrees.y()) / SCALE_SPEED;

        canvas->change_scale(ky);
        canvas->draw(cur_func, ui->x_min->text().toDouble(), ui->x_max->text().toDouble(),
                        ui->x_step->text().toDouble(), ui->z_min->text().toDouble(),
                        ui->z_max->text().toDouble(), ui->z_step->text().toDouble());

        canvas->update();
    }
}

void MainWindow::on_SemiPenColor_comboBox_activated(int index)
{
    switch (index)
    {
        case 0:
            canvas->set_fg(Qt::black);
            break;
        case 1:
            canvas->set_fg(Qt::red);
            break;
        case 2:
            canvas->set_fg(Qt::darkGreen);
            break;
        case 3:
            canvas->set_fg(Qt::blue);
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
            //canvas->setStyleSheet("background-color:white;");
            canvas->set_bg(Qt::white);
            break;
        case 1:
            //canvas->setStyleSheet("background-color:blue;");
            canvas->set_bg(Qt::blue);
            break;
        case 2:
            //canvas->setStyleSheet("background-color:blue;");
            canvas->set_bg(Qt::red);
            break;
        case 3:
            //canvas->setStyleSheet("background-color:green;");
            canvas->set_bg(Qt::darkGreen);
            break;
        case 4:
            //canvas->setStyleSheet("background-color:black;");
            canvas->set_bg(Qt::black);
            break;
        default:
            //???
            break;
    }
}

void MainWindow::on_cut_col_btn_clicked()
{
}

void MainWindow::on_pushButton_clicked()
{
    canvas->draw(cur_func, ui->x_min->text().toDouble(), ui->x_max->text().toDouble(),
                    ui->x_step->text().toDouble(), ui->z_min->text().toDouble(),
                    ui->z_max->text().toDouble(), ui->z_step->text().toDouble());
}

void MainWindow::on_clean_Btn_clicked()
{
    canvas->clear();
    //canvas->clean();
}

/*void MainWindow::on_end_cutter_clicked()
{
    canvas->set_scale(ui->scale->text().toDouble());
    double (*f)(double x, double z);
    if (ui->comboBox->currentIndex() == 0)
        f = func3;
    else if (ui->comboBox->currentIndex() == 1)
        f = func4;
    else if (ui->comboBox->currentIndex() == 2)
        f = func2;
    else
        f = func1;
    canvas->draw(f, ui->x_min->text().toDouble(), ui->x_max->text().toDouble(),
                    ui->x_step->text().toDouble(), ui->z_min->text().toDouble(),
                    ui->z_max->text().toDouble(), ui->z_step->text().toDouble());
}*/

void MainWindow::on_rotate_clicked()
{
    canvas->rotate_x(ui->angle_x->text().toDouble());
    canvas->rotate_y(ui->angle_y->text().toDouble());
    canvas->rotate_z(ui->angle_z->text().toDouble());

    canvas->draw(cur_func, ui->x_min->text().toDouble(), ui->x_max->text().toDouble(),
                    ui->x_step->text().toDouble(), ui->z_min->text().toDouble(),
                    ui->z_max->text().toDouble(), ui->z_step->text().toDouble());
}

void MainWindow::on_comboBox_activated(int index)
{
    cout << index << endl;
    switch (index)
    {
    case 0:
        cur_func = func1;
        break;
    case 1:
        cur_func = func2;
        break;
    case 2:
        cur_func = func3;
        break;
    case 3:
        cur_func = func4;
        break;
    case 4:
        cur_func = func5;
        break;
    default:
        //????
        break;
    }
}
