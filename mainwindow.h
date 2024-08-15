#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "connectthread.h"
#include<QTableWidget>
#include<QTableView>
#include <QStandardItemModel>

#include <QtCharts/QtCharts>
#include <QtCharts/QChartView>

#include <QtCore/QTimer>

#include "mythread.hpp"
#include<OpenXLSX.hpp>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT


    std::vector<SimpleBLE::Adapter> adapter_list;
    SimpleBLE::Adapter adapter;
    std::vector<SimpleBLE::Peripheral> peripherals;
    SimpleBLE::Peripheral peripheral_connected;

 

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_bt_connect_clicked();
    void measure_data_slot(float x);
    void handleTimeout();
    void handleTimeout_cv();
    

private:
    QTimer m_timer;
    QTimer m_timer_cv;
    Ui::MainWindow *ui;
    ConnectThread *p_connect;
    //QTableWidget *data_table;
    QStandardItemModel *data_table;
    QTableView   *myTableView;

    QChartView *ChartCurrentView;
    QChart     *ChartCurrent;
    QLineSeries *series_current;
    QValueAxis *m_current_axisX;
    QValueAxis *m_current_axisY;


    QChartView *ChartCVView ;
    QChart     *ChartCV;
    QLineSeries *series_cv ;
    QValueAxis *m_cv_axisX;
    QValueAxis *m_cv_axisY; 


    my_Thread pMyThread;

    OpenXLSX::XLDocument *pDoc;
    

};
#endif // MAINWINDOW_H
