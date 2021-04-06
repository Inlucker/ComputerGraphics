#include "stageform.h"
#include "ui_stageform.h"

StageForm::StageForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StageForm)
{
    ui->setupUi(this);

    setLayout(ui->gridLayout);
}

StageForm::~StageForm()
{
    delete ui;
}

void StageForm::makePlot(QVector<double> x, QVector<double> y, int n)
{
    if (n >0)
    {
        double x_min = x[0], x_max = x[0], y_min = y[0], y_max = y[0];
        // generate some data:
        //QVector<double> x(101), y(101); // initialize with entries 0..100
        for (int i = 0; i<n; ++i)
        {
            if (x_min > x[i])
                x_min = x[i];
            if (x_max < x[i])
                x_max = x[i];

            if (y_min > y[i])
                y_min = y[i];
            if (y_max < y[i])
                y_max = y[i];
            //x[i] = i/50.0 - 1; // x goes from -1 to 1
            //y[i] = x[i]*x[i]; // let's plot a quadratic function
        }
        // create graph and assign data to it:
        ui->customPlot->addGraph();
        ui->customPlot->graph(0)->setData(x, y);
        // give the axes some labels:
        ui->customPlot->xAxis->setLabel("x");
        ui->customPlot->yAxis->setLabel("y");
        // set axes ranges, so we see all data:
        //ui->customPlot->xAxis->setRange(-1, 1);
        //ui->customPlot->yAxis->setRange(0, 1);
        ui->customPlot->xAxis->setRange(x_min, x_max);
        ui->customPlot->yAxis->setRange(y_min, y_max);
        ui->customPlot->replot();
    }
}
