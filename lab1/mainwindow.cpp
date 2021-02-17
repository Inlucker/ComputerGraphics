#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "calculations.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setFixedHeight(this->height());
    this->setFixedWidth(this->width());

    ui->tableWidget->setRowCount(3);
    cur_dots_number = 3;
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "X" << "Y");

    //ui->tableWidget->setColumnWidth(0, ui->tableWidget->width() / 2 - 8);
    //ui->tableWidget->setColumnWidth(1, ui->tableWidget->width() / 2 - 8);

    for (int i = 0; i < ui->tableWidget->rowCount(); i++)
        for (int j = 0; j < ui->tableWidget->columnCount(); j++)
        {
            QTableWidgetItem *itm = new QTableWidgetItem(tr("%1").arg((rand() % 100 - 50)*5));

            ui->tableWidget->setItem(i, j, itm);
        }

    myPicture = new MyGraphicsView();
    ui->gridLayout->addWidget(myPicture);
    myPicture->setStyleSheet("background-color:white;");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_enterDotsNumberBtn_clicked()
{
    QString text = ui->lineEdit->text();
    bool isInt = false;
    int tmp = text.toInt(&isInt);
    if (isInt && tmp >= 0 && tmp <= MAX_POINT_NUMBER)
    {
        ui->tableWidget->setRowCount(tmp);
        for (int i = 0; i < ui->tableWidget->rowCount(); i++)
        {
            if (i > cur_dots_number - 1)
            {
                QTableWidgetItem *itm_x = new QTableWidgetItem(tr("%1").arg((rand() % 100 - 50)*5));
                ui->tableWidget->setItem(i, 0, itm_x);

                QTableWidgetItem *itm_y = new QTableWidgetItem(tr("%1").arg((rand() % 100 - 50)*5));
                ui->tableWidget->setItem(i, 1, itm_y);
            }
        }
        cur_dots_number = tmp;
        //ui->tableWidget->setColumnCount(2);
    }
    else
    {
        QMessageBox::information(this, "Error", tr("Нужно ввести целое число принадлежащее интервалу [0; %1]").arg(MAX_POINT_NUMBER));
    }
}

void MainWindow::on_outputBtn_clicked()
{
    if (cur_dots_number < 3)
    {
        ui->result_label->setText("Недостаточно точек для построения треугольника - нет решения");
        QMessageBox::information(this, "Error", "Недостаточно точек для построения треугольника");
        return;
    }

    pair<int, int> dots[cur_dots_number];
    myPicture->clearPoints();
    for (int i = 0; i < cur_dots_number; i++)
    {
        QString xText = ui->tableWidget->item(i, 0)->text();
        bool xIsInt = false;
        int x = xText.toInt(&xIsInt);

        QString yText = ui->tableWidget->item(i, 1)->text();
        bool yIsInt = false;
        int y = yText.toInt(&yIsInt);

        if (xIsInt && yIsInt)
        {
            QPen penBlack(Qt::black); // Задаём чёрную кисть
            dots[i].first = x;
            dots[i].second = y;
        }
        else
        {
            ui->result_label->setText("Некорректные исходные данные");
            QMessageBox::information(this, "Error", "Все координаты должны быть целыми числами");
            return;
        }
    }

    myPicture->points_mn = new pair<int, int> [cur_dots_number];
    for (int i = 0; i < cur_dots_number; i++)
    {
        myPicture->points_mn[i] = dots[i];
    }
    myPicture->points_number = cur_dots_number;


    //here

    int max_dif = -1;
    /*int rez_x1;
    int rez_y1;
    int rez_x2;
    int rez_y2;
    int rez_x3;
    int rez_y3;*/

    int c = 0;

    /*int cur_ids[THREE] = {0, 1, 2};
    int tmp = get_max_dif(dots, ui->tableWidget->rowCount(), cur_ids);
    if (tmp > max_dif)
    {
        max_dif = tmp;

        myPicture->rez_x1 = dots[0].first;
        myPicture->rez_y1 = dots[0].second;
        myPicture->rez_x2 = dots[1].first;
        myPicture->rez_y2 = dots[1].second;
        myPicture->rez_x3 = dots[2].first;
        myPicture->rez_y3 = dots[2].second;

        myPicture->id1 = 0 + 1;
        myPicture->id2 = 1 + 1;
        myPicture->id3 = 2 + 1;
    }*/

    for (int i = 0; i < cur_dots_number - 2; i++)
    {
        for (int j = i + 1; j < cur_dots_number - 1; j++)
        {
            for (int k = j + 1; k < cur_dots_number; k++)
            {
                int cur_ids[THREE] = {i, j , k};
                int tmp = get_max_dif(dots, cur_dots_number, cur_ids);
                c++;
                //cout << "i = " << i << "; j = "<< j << "; k = " << k << "; c = " << c << "; tmp = " << tmp << endl;
                if (tmp > max_dif)
                {
                    max_dif = tmp;

                    myPicture->rez_x1 = dots[i].first;
                    myPicture->rez_y1 = dots[i].second;
                    myPicture->rez_x2 = dots[j].first;
                    myPicture->rez_y2 = dots[j].second;
                    myPicture->rez_x3 = dots[k].first;
                    myPicture->rez_y3 = dots[k].second;

                    myPicture->id1 = i + 1;
                    myPicture->id2 = j + 1;
                    myPicture->id3 = k + 1;
                }
            }
        }
    }
    //cout << max_dif << endl;
    myPicture->update();

    if (max_dif == -1)
    {
        ui->result_label->setText("Все точки на одной прямой - нет решения");
        QMessageBox::information(this, "Error", "Все точки на одной прямой");
    }
    else
    {
        myPicture->rez = true;
        ui->result_label->setText(tr("Максимальная разница кол-ва точек в треугольниках образованных медианами: %1\n"
        "Точки образующие результирующий треугольник: #%2 (%3; %4)    #%5 (%6; %7)    #%8 (%9; %10)").
                                  arg(max_dif).
                                  arg(myPicture->id1).arg(myPicture->rez_x1).arg(myPicture->rez_y1).
                                  arg(myPicture->id2).arg(myPicture->rez_x2).arg(myPicture->rez_y2).
                                  arg(myPicture->id3).arg(myPicture->rez_x3).arg(myPicture->rez_y3));
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Delete)
    {
        QModelIndexList selectedRows = ui->tableWidget->selectionModel()->selectedRows();
        while (!selectedRows.empty())
        {
            ui->tableWidget->removeRow(selectedRows[0].row());
            selectedRows = ui->tableWidget->selectionModel()->selectedRows();
        }
        cur_dots_number = ui->tableWidget->rowCount();
    }
    else if (event->key() == 16777220) //Qt::Key_Enter) //61 +
    {
        if (cur_dots_number < MAX_POINT_NUMBER)
        {
            ui->tableWidget->setRowCount(cur_dots_number + 1);
            QTableWidgetItem *itm_x = new QTableWidgetItem(tr("%1").arg((rand() % 100 + 1)*5));
            ui->tableWidget->setItem(cur_dots_number, 0, itm_x);

            QTableWidgetItem *itm_y = new QTableWidgetItem(tr("%1").arg((rand() % 100 + 1)*5));
            ui->tableWidget->setItem(cur_dots_number, 1, itm_y);
            cur_dots_number++;
            ui->tableWidget->scrollToBottom();
        }
        else
        {
            QMessageBox::information(this, "Error", tr("Максимальное кол-во точек %1.\nНельзя ввести больше").arg(MAX_POINT_NUMBER));
        }
    }
    else
    {
        cout << event->key() << endl;
    }
}
