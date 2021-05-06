#ifndef CIRCLETIMEGRAPHS_H
#define CIRCLETIMEGRAPHS_H

#include <QWidget>
#include <QtCharts>

#define I_RADIUS (i+1)*100

namespace Ui {
class CircleTimeGraphs;
}

class CircleTimeGraphs : public QWidget
{
    Q_OBJECT

public:
    explicit CircleTimeGraphs(QWidget *parent = nullptr);
    ~CircleTimeGraphs();

    void makePlot(int n, double **funcs, bool isCircle);
    void makePlot2(int n, double **funcs);
private:
    Ui::CircleTimeGraphs *ui;
    QChartView *chartView;
};

#endif // CIRCLETIMEGRAPHS_H
