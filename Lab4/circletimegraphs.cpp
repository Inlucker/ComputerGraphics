#include "circletimegraphs.h"
#include "ui_circletimegraphs.h"

CircleTimeGraphs::CircleTimeGraphs(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CircleTimeGraphs)
{
    ui->setupUi(this);

    setLayout(ui->gridLayout_3);

    chartView = new QChartView();
    chartView->setRenderHint(QPainter::Antialiasing);

    //plase it in this widget

    ui->gridLayout_3->addWidget(chartView);

    /*QChart *chart = new QChart();

    //prepare data
    QLineSeries *series = new QLineSeries();
    QLineSeries *series2 = new QLineSeries();

    for (int i=0;i<100;i++)
    {
        series->append(i, i*i);
        series2->append(i, i*10);
    }

    //name it
    series->setName("Square");
    series2->setName("Multiplied by 10");

    //add data series ti the chart
    chart->addSeries(series);
    chart->addSeries(series2);

    //hide legend if needed
    //chart->legend()->hide();

    //specify legend position
    chart->legend()->setAlignment(Qt::AlignBottom);

    //set chart title
    chart->setTitle("QT Charts example");

    //add axis to the chart
    QDateTimeAxis *axisX = new QDateTimeAxis;
    axisX->setTickCount(10);
    axisX->setFormat("MMM yyyy");
    axisX->setTitleText("Date");
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis;
    axisY->setLabelFormat("%i");
    axisY->setTitleText("Money");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    //create new view
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    //plase it in this widget

    ui->gridLayout_3->addWidget(chartView);*/
   //setCentralWidget(chartView);
}

#include <iostream>

using namespace std;

void CircleTimeGraphs::makePlot(int n, double **funcs, bool isCircle)
{
    QChart *chart = new QChart();

    //prepare data
    QLineSeries *conanSeries = new QLineSeries();
    QLineSeries *paramSeries = new QLineSeries();
    QLineSeries *brezSeries = new QLineSeries();
    QLineSeries *midpointSeries = new QLineSeries();
    QLineSeries *qtSeries = new QLineSeries();

    for (int i = 0; i < n;i++)
    {
        conanSeries->append(I_RADIUS, funcs[0][i]);
        paramSeries->append(I_RADIUS, funcs[1][i]);
        brezSeries->append(I_RADIUS, funcs[2][i]);
        midpointSeries->append(I_RADIUS, funcs[3][i]);
        qtSeries->append(I_RADIUS, funcs[4][i]);
    }

    //name it
    conanSeries->setName("Каноническое уравнение");
    paramSeries->setName("Параметрическое уравнение");
    brezSeries->setName("Алгоритм Брезенхема");
    midpointSeries->setName("Алгоритм средней точки");
    qtSeries->setName("QT");

    //add data series ti the chart
    chart->addSeries(conanSeries);
    chart->addSeries(paramSeries);
    chart->addSeries(brezSeries);
    chart->addSeries(midpointSeries);
    chart->addSeries(qtSeries);

    //hide legend if needed
    //chart->legend()->hide();

    //specify legend position
    chart->legend()->setAlignment(Qt::AlignBottom);

    //set chart title
    if (isCircle)
        chart->setTitle("Оценка времени построения окружностей");
    else
        chart->setTitle("Оценка времени построения окружностей эллипсов");

    //add axis to the chart
    QValueAxis *axisX = new QValueAxis;
    axisX->setTickCount(10);
    axisX->setLabelFormat("%d");
    axisX->setTitleText("Радиус");
    chart->addAxis(axisX, Qt::AlignBottom);
    conanSeries->attachAxis(axisX);
    paramSeries->attachAxis(axisX);
    brezSeries->attachAxis(axisX);
    midpointSeries->attachAxis(axisX);
    qtSeries->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis;
    axisY->setLabelFormat("%f");
    axisY->setTitleText("Время");
    chart->addAxis(axisY, Qt::AlignLeft);
    paramSeries->attachAxis(axisY);
    conanSeries->attachAxis(axisY);
    brezSeries->attachAxis(axisY);
    midpointSeries->attachAxis(axisY);
    qtSeries->attachAxis(axisY);

    //chart->createDefaultAxes();
    cout << "Ymax = " << axisY->max() << endl;
    axisY->setRange(0.00, axisY->max()*1.1);// I dont know how to get real max, not paramSeries max(
    ui->gridLayout_3->removeWidget(chartView);

    //create new view
    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMouseTracking(true);

    //plase it in this widget

    ui->gridLayout_3->addWidget(chartView);
}

CircleTimeGraphs::~CircleTimeGraphs()
{
    delete ui;
}
