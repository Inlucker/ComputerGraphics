#ifndef STAGEFORM_H
#define STAGEFORM_H

#include <QWidget>
#include "canvas.h"

namespace Ui {
class StageForm;
}

class StageForm : public QWidget
{
    Q_OBJECT

public:
    explicit StageForm(QWidget *parent = nullptr);
    ~StageForm();

    void makePlot(QVector<double> x, QVector<double> y, int n, Algoritm alg);
private:
    Ui::StageForm *ui;
};

#endif // STAGEFORM_H
