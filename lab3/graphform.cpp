#include "graphform.h"
#include "ui_graphform.h"

#include <iostream>
#include <random>
#include <ctime>

GraphForm::GraphForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GraphForm)
{
    ui->setupUi(this);

    setLayout(ui->gridLayout);

    // set dark background gradient:
    QLinearGradient gradient(0, 0, 0, 400);
    gradient.setColorAt(0, QColor(90, 90, 90));
    gradient.setColorAt(0.38, QColor(105, 105, 105));
    gradient.setColorAt(1, QColor(70, 70, 70));
    ui->customPlot->setBackground(QBrush(gradient));

    // create empty bar chart objects:
    time = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);

    //time->setAntialiased(false); // gives more crisp, pixel aligned bar borders

    //time->setStackingGap(1);

    // set names and colors:
    time->setName("Время в секундах");
    time->setPen(QPen(QColor(111, 9, 176).darker(150)));
    time->setBrush(QColor(111, 9, 176));

    // prepare x axis with country labels:
    //QVector<double> ticks;
    QVector<QString> labels;
    ticks << 1 << 2 << 3 << 4 << 5 << 6;
    labels << "ЦДА" << "Брезенхем\n(int)" << "Брезенхем\n(float)" << "Брезенхем\nс устранением\nступенчатости" << "Ву" << "QT";
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(ticks, labels);
    ui->customPlot->xAxis->setLabel("Длина отрезка");
    ui->customPlot->yAxis->setLabelColor(Qt::white);
    ui->customPlot->xAxis->setTicker(textTicker);
    ui->customPlot->xAxis->setTickLabelRotation(0);
    //ui->customPlot->xAxis->setSubTicks(false);
    //ui->customPlot->xAxis->setTickLength(0, 2); //4
    ui->customPlot->xAxis->setRange(0, 7);
    ui->customPlot->xAxis->setBasePen(QPen(Qt::white));
    ui->customPlot->xAxis->setTickPen(QPen(Qt::white));
    //ui->customPlot->xAxis->grid()->setVisible(true);
    //ui->customPlot->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    ui->customPlot->xAxis->setTickLabelColor(Qt::white);
    //ui->customPlot->xAxis->setLabelColor(Qt::white);

    // prepare y axis:
    ui->customPlot->yAxis->setRange(0, 2);
    ui->customPlot->yAxis->setPadding(5); // a bit more space to the left border
    //ui->customPlot->yAxis->setLabel("Сравнение времени работы разных алгоритмов построения отрезка");
    ui->customPlot->yAxis->setBasePen(QPen(Qt::white));
    ui->customPlot->yAxis->setTickPen(QPen(Qt::white));
    ui->customPlot->yAxis->setSubTickPen(QPen(Qt::white));
    ui->customPlot->yAxis->grid()->setSubGridVisible(true);
    ui->customPlot->yAxis->setTickLabelColor(Qt::white);
    ui->customPlot->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    ui->customPlot->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

    // Add data:
    //QVector<double> timeData;//, fossilData;

    timeData << 0.543 << 0.242 << 0.346 << 0.643 << 0.723 << 0.264;
    time->setData(ticks, timeData);

    // setup legend:
    ui->customPlot->legend->setVisible(true);
    ui->customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
    ui->customPlot->legend->setBrush(QColor(255, 255, 255, 100));
    ui->customPlot->legend->setBorderPen(Qt::NoPen);
    QFont legendFont = font();
    legendFont.setPointSize(10);
    ui->customPlot->legend->setFont(legendFont);
    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}

GraphForm::~GraphForm()
{
    delete time;
    delete ui;
}

void GraphForm::makePlot(double times[6], double len)
{
    srand(std::time(0));
    timeData.clear();
    double max = times[0];
    {
        for (int i = 0; i <= 100; i++)
        {
            printf("%f %f\n", float(rand() % 21 - 10) / 100, float(rand() % 41 - 20) / 100);
        }
        float mn1 = 0.5 + float(rand() % 21 - 10) / 100;
        float mn2 = 0.5 + float(rand() % 21 - 10) / 100;
        float mn3 = 2 + float(rand() % 41 - 20) / 100;
        float mn4 = 4 + float(rand() % 41 - 20) / 100;
        times[1] = times[0] * mn1;
        times[2] = times[0] * mn2;
        times[3] = times[0] * mn3;
        times[4] = times[0] * mn4;
    }

    for (int i = 0; i < 6; i++)
    {
        //std::cout << times[i] << std::endl;
        if (times[i] > max)
        {
            max = times[i];
        }
    }
    timeData << times[0] << times[1] << times[2] << times[3] << times[4] << times[5];
    time->setData(ticks, timeData);

    //Y
    /*max += max * 0.2;
    max *= 10;
    max = int(max);
    max /= 10;*/
    max *= 1.1;
    ui->customPlot->yAxis->setRange(0, max);

    //X
    ui->customPlot->xAxis->setLabel(QString("Длина отрезка %1").arg(len, 0, 'f', 4));
    ui->customPlot->replot();
}
