#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "canvas.h"
#include "graphform.h"
#include "stageform.h"
#include <QMainWindow>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_draw_Btn_clicked();

    void on_clean_Btn_clicked();

    void on_penColor_comboBox_activated(int index);

    void on_backgroundColor_comboBox_activated(int index);

    void on_method_comboBox_activated(int index);

    void on_Create_Spectre_Btn_clicked();
    void on_show_graphs_Btn_clicked();

    void on_stage_Btn_clicked();

private:
    Ui::MainWindow *ui;

    Canvas *canvas;

    GraphForm* graphForm;
    StageForm* stageForm;

    void getXYs(QVector<double> *x, QVector<double> *y, int *n, double length, Algoritm method);

    int sign(double val);
    int getStairsDGA(int X_start, int X_end, int Y_start, int Y_end);
    int getStairsBrezenheimInt(int X_start, int X_end, int Y_start, int Y_end);
    int getStairsBrezenheimFloat(int X_start, int X_end, int Y_start, int Y_end);
    int getStairsBrezenheimSmooth(int X_start, int X_end, int Y_start, int Y_end);
    int getStairsVu(int X_start, int X_end, int Y_start, int Y_end);
};
#endif // MAINWINDOW_H
