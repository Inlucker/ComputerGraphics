#ifndef GRAPHFORM_H
#define GRAPHFORM_H

#include <QWidget>
#include <qcustomplot.h>

namespace Ui {
class GraphForm;
}

class GraphForm : public QWidget
{
    Q_OBJECT

public:
    explicit GraphForm(QWidget *parent = nullptr);
    ~GraphForm();

    void makePlot(double times[], double len);
private:
    Ui::GraphForm *ui;
    QCPBars *time;
    QVector<double> ticks;
    QVector<double> timeData;
};

#endif // GRAPHFORM_H
