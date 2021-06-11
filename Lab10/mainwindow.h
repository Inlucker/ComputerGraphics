#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QColor>
#include <QColorDialog>
#include <QMessageBox>
#include "canvas.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
   //virtual void mousePressEvent(QMouseEvent *event);

private slots:
    void on_SemiPenColor_comboBox_activated(int index);

    void on_backgroundColor_comboBox_activated(int index);

    void on_clean_Btn_clicked();

    /*void on_seg_col_btn_clicked();

    void on_vis_part_col_btn_clicked();*/

    void on_cut_col_btn_clicked();

    void on_pushButton_clicked();

    void on_end_cutter_clicked();

    void on_end_enter_clicked();

    void on_rotate_y_clicked();

    void on_rotate_z_clicked();

private:
    Ui::MainWindow *ui;
    Canvas *canvas;
};
#endif // MAINWINDOW_H
