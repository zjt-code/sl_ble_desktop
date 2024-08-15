#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "simpleble/Adapter.h"
#include "simpleble/SimpleBLE.h"

#include "user_service.h"
#include "mythread.hpp"

#include<iostream>
#include<string>
#include <iomanip>
#include <sstream>

// User fACE layout
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QFormLayout>
#include<QGridLayout>
#include<QDebug>
#include<QTextBrowser>
#include<QTableWidget>


#include<QtCharts/QChartView>
#include<QtCharts/QtCharts>
#include<QAbstractAxis>


#include<QPushButton>
#include<OpenXLSX.hpp>

#include<QDateTime>
#include<QTime>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , ChartCurrentView(new QChartView)
    , ChartCurrent(new QChart)
    , series_current(new QLineSeries)
    , m_current_axisX(new QValueAxis)
    , m_current_axisY(new QValueAxis)
    , p_connect(new ConnectThread)
    , ChartCVView(new QChartView)
    , ChartCV(new QChart)
    , series_cv(new QLineSeries)
    , m_cv_axisX(new QValueAxis)
    , m_cv_axisY(new QValueAxis)
    , myTableView(new QTableView)
    , data_table(new QStandardItemModel)
   , pDoc(new OpenXLSX::XLDocument)
{


    //
    ui->setupUi(this);
    // add singal and slot    
    QObject::connect(&m_timer, &QTimer::timeout, this, &MainWindow::handleTimeout);
    m_timer.setInterval(100);
  // m_timer.start();

    QObject::connect(&m_timer_cv,&QTimer::timeout,this,&MainWindow::handleTimeout_cv);
    m_timer_cv.setInterval(50);
   //m_timer_cv.start();

    connect(p_connect, SIGNAL(SignalMeasureData(float)),this,SLOT(measure_data_slot(float)));


    // p_connect = new ConnectThread(this); 
    std::cout<<" Mainwindow construct"<<std::endl;

   // pMyThread.start();

    // interface layout

    //creat widget, added to mainwindow
    // used to add layout
    QWidget *MainWidget = new QWidget();

    QVBoxLayout *button_Layout = new QVBoxLayout();
    QVBoxLayout *button_Layout_chirld = new QVBoxLayout();

    QPushButton *p_BT1 = new QPushButton();
    QPushButton *p_BT2 = new QPushButton();

    p_BT1->setText("BT1");
    p_BT2->setText("BT2");

    button_Layout_chirld->addWidget(ui->pushButton);
    button_Layout_chirld->addWidget(ui->bt_connect);

    button_Layout_chirld->addWidget(p_BT1);
    button_Layout_chirld->addWidget(p_BT2);   

    button_Layout->addLayout(button_Layout_chirld);
    button_Layout->setAlignment(button_Layout_chirld,Qt::AlignBottom);

    // button_Layout->insertSpacing(0,300);
    // button_Layout->insertSpacing(4,-1);
    //button_Layout->setDirection(QBoxLayout::RightToLeft);
    // button_Layout->setSpacing(20);
   

   // button_Layout->setAlignment(Qt::AlignBottom);
    // button_Layout->setSpacing(10);

    std::cout<<"button alignment"<<button_Layout->alignment()<<std::endl;
    std::cout<< "butoton space = "<< button_Layout->spacing() <<std::endl;

    // add charview current

    QVBoxLayout *ChartLayout = new QVBoxLayout();
    
    ChartCurrent->addSeries(series_current);

    m_current_axisY->setRange(Y_AVIX_DEFAULT_MIN,Y_AVIX_DEFAULT_MAX);
    m_current_axisX->setRange(0,20);
    m_current_axisY->setLabelsColor(QColor(255,0,0));

   // m_current_axisX->setTickCount(10);
     m_current_axisX->setLabelFormat("%d");
     m_current_axisX->setLabelsColor(QColor(255,0,0));


    ChartCurrent->addAxis(m_current_axisX,Qt::AlignBottom);
    series_current->attachAxis(m_current_axisX);
    ChartCurrent->addAxis(m_current_axisY,Qt::AlignLeft);
    series_current->attachAxis(m_current_axisY);    

    series_current->setColor(QColor(255,0,0));

    ChartCurrent->legend()->hide();
    ChartCurrent->setTitle("Measurement Diff Voltage");
    ChartCurrent->setTitleBrush(QBrush(QColor(255,0,0)));
    ChartCurrent->setBackgroundBrush(QBrush(QColor(255,255,255)));

    ChartCurrentView->setChart(ChartCurrent);
    ChartCurrentView->setBackgroundBrush(QBrush(QColor(255,255,255)));   


    // add cv chart

    m_cv_axisX->setRange(0,100);
    m_cv_axisX->setLabelFormat("%d");
    m_cv_axisX->setLabelsColor(QColor(255,0,0));

    m_cv_axisY->setRange(-5,5);
    m_cv_axisY->setLabelsColor(QColor(255,0,0));

    series_cv->setColor(QColor(255,0,0));
    ChartCV->addSeries(series_cv);

    ChartCV->addAxis(m_cv_axisX,Qt::AlignBottom);
    series_cv->attachAxis(m_cv_axisX);
    ChartCV->addAxis(m_cv_axisY,Qt::AlignLeft);
    series_cv->attachAxis(m_cv_axisY);
    
    ChartCV->legend()->hide();
    ChartCV->setTitle("CV(100 value)");
    ChartCV->setTitleBrush(QBrush(QColor(255,0,0)));

    ChartCV->setBackgroundBrush(QBrush(QColor(255,255,255)));

    ChartCVView->setChart(ChartCV);
    ChartCVView->setBackgroundBrush(QBrush(QColor(255,255,255)));


    //ChartCurrent->addSeries(series_cv);
    // add to layout
    ChartLayout->addWidget(ChartCurrentView);
    ChartLayout->addWidget(ChartCVView);

    // // addtable
    
     myTableView->setModel(data_table);
     myTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
     data_table->setColumnCount(3);
     data_table->setHorizontalHeaderLabels({"I_CURRENT","CV(100)"});
     myTableView->setShowGrid(true);
     

    std::cout<<"table-row"<<data_table->rowCount()<<std::endl;

         //QFormLayout *MainForm_Layout = new QFormLayout();
    QGridLayout *MainGrid_Layout = new QGridLayout();
    QTextBrowser *info_text = new QTextBrowser();

    info_text->append("test text brower");

    MainGrid_Layout->addWidget(myTableView,0,0);
    MainGrid_Layout->addLayout(ChartLayout,0,1);
    MainGrid_Layout->addLayout(button_Layout,0,2);
    MainGrid_Layout->addWidget(info_text,1,0,1,3);

    std::cout<<" main grid columstrech "<<MainGrid_Layout->columnCount()<<std::endl;

    MainGrid_Layout->setColumnStretch(1,1);


    qDebug()<<MainGrid_Layout->rowCount();

    MainWidget->setLayout(MainGrid_Layout);

    setCentralWidget(MainWidget);


    std::string path="nxj_evb_test.xlsx";
    try
    {
        pDoc->create(path); 

        auto wks_cur = pDoc->workbook().worksheet("Sheet1");

        wks_cur.cell("A1").value() = "Index";
        wks_cur.cell("B1").value() = "Current(nA)";
        wks_cur.cell("C1").value() = "Time";

        pDoc->save();     // std::cout<<"current row -->"<<wks_cur.rowCount()<<std::endl;        
        pDoc->close();
    }catch(...)
    {
     
       std::cout<<"exception create path"<<std::endl;
    }

    std::cout<<QTime::currentTime().toString().toStdString()<<std::endl;

 
}


MainWindow::~MainWindow()
{
    delete p_connect;
    delete data_table;
    delete ui;
    
}

qreal a=0,b=0;


qreal Y_max=Y_AVIX_DEFAULT_MIN,Y_min=Y_AVIX_DEFAULT_MIN;


void MainWindow::handleTimeout()
{

    Y_max = (Y_max > 10*sin(b*0.2f)) ? Y_max: 10*sin(b*0.2f);

    Y_min = (Y_min < 10*sin(b*0.2f)) ? Y_min: 10*sin(b*0.2f);

    if( a > 200 )
        m_current_axisX->setRange(a+1-200,a+1);
    else
        m_current_axisX->setRange(0,a+1);

    m_current_axisY->setRange(Y_min,Y_max);

    std::cout<<" 1S timeout = "<< a << " value :"<<10*sin(b*0.2f)<<std::endl;

    series_current->append(a,10*sin(b*0.2f));
    
    //series_current->show();


    a++;
    b++;
}


qreal c=0,d=0;


qreal U_max=0,V_min=0;


void MainWindow::handleTimeout_cv()
{


    U_max = (U_max > 5*sin(b*0.2f)) ? U_max: 5*sin(b*0.2f);

    V_min = (V_min < 5*sin(b*0.2f)) ? V_min: 5*sin(b*0.2f);

    if( a > 100 )
        m_cv_axisX->setRange(a+1-100,a+1);
    else
        m_cv_axisX->setRange(0,a+1);

    m_cv_axisY->setRange(V_min,U_max);



    std::cout<<" 1S timeout = "<< a << " value :"<<5*sin(b*0.2f)<<std::endl;

    series_cv->append(a,5*sin(b*0.2f));
    


}

void MainWindow::on_pushButton_clicked()
{

    std::cout<<"connected is pressed"<<std::endl;


    adapter_list=SimpleBLE::Adapter::get_adapters();

        if (adapter_list.size() == 0)
        {
            // debugstr= "No adapter was found.";
            std::cout<<" No adapter was found"<<std::endl;
            //ui->DebugInfoBrower->append(QString::fromStdString(debugstr));
            return;
        }
        else{ std::cout<<" adtper ="<< adapter_list.size()<<std::endl;}


        adapter = adapter_list[0];

        adapter.set_callback_on_scan_start([]() { std::cout << "Scan started." << std::endl; });

        adapter.set_callback_on_scan_stop([]() { std::cout << "Scan stopped." << std::endl; });

        adapter.set_callback_on_scan_found([&](SimpleBLE::Peripheral peripheral){
            std::cout << "Signal Found device: " << peripheral.identifier()<< " [" << peripheral.address()<< "]" << std::endl;
            peripherals.push_back(peripheral);
            
            
            // the device name conneted
            if(peripheral.identifier().compare("Empty Example")==0)
            {
                std::cout<<"Found "<< peripheral.identifier()<<"  stop scan"<<std::endl;

                adapter.scan_stop();

                peripheral_connected = peripheral;
                
                // p_connect->peripheral_connected = peripheral;
                                        
                //SignalBleDeviceConnect(peripheral);
            }
    });

    adapter.scan_start();


}

void MainWindow::on_bt_connect_clicked()
{

    //connecting
    p_connect->peripheral_connected = peripheral_connected;

    std::cout<<"connecting -----"<<std::endl;

    std::cout<< p_connect<<std::endl;

    p_connect->start();

   // p_connect->cgms_test();  

   // pMyThread->start();



}



static int data_i_row = 0;
std::vector<float> cur_data_arr{0};


void MainWindow::measure_data_slot(float x)
{

    // QStandardItem   *cur_item = new QStandardItem("abcedf");
    
        std::cout<<"slot = " << x <<std::endl;

    // QTableWidgetItem *cur_item = new QTableWidgetItem("abcef");

    
        QStandardItem *cur_item = new QStandardItem(QString::number(x));

        cur_item->setTextAlignment(Qt::AlignCenter);
        //cur_item->setEditable(false);

        cur_item->setTextAlignment(Qt::AlignCenter);
        cur_item->setEditable(false);
        data_table->setRowCount(data_i_row+1);
        data_table->setItem(data_i_row++,0,cur_item); 
        myTableView->scrollToBottom(); 

        // update buffer
        if(cur_data_arr.size()<100)
        {
            cur_data_arr.push_back(x);
        }
        else
        {
            for(uint i =0; i < cur_data_arr.size()-1; i++){
                    cur_data_arr[i]=cur_data_arr[i+1];
                }
                    cur_data_arr[cur_data_arr.size()-1] = x;
                }

        


    Y_max = (Y_max > x) ? Y_max: x;

    Y_min = (Y_min < x) ? Y_min: x;

    if( a > 100 )
        m_current_axisX->setRange(a+1-100,a+1);
    else
        m_current_axisX->setRange(0,a+1);

    m_current_axisY->setRange(Y_min,Y_max+10);
      
    series_current->append(data_i_row,x);
    m_current_axisX->setRange(0,data_i_row);

        // ChartCurrent->scroll(1,0);
        // ChartCurrentView->resetCachedContent();
        //ChartCurrent->addSeries(series_current);
        // ChartCurrent->createDefaultAxes();


    /****************save data to excel***************** */ 
    std::string path="nxj_evb_test.xlsx";
    try
    {
        pDoc->open(path);
        std::cout<< pDoc->isOpen()<<std::endl;;
        //pDoc->

        std::cout<<"write data to " << path<< std::endl;
        //pDoc->open(path);
         auto wks_cur = pDoc->workbook().worksheet("Sheet1");
         int cur_row = wks_cur.rowCount();
         std::string a_row_cnt = "A" + std::to_string(cur_row +1);
         std::string b_row_cnt = "B" + std::to_string(cur_row +1);
         std::string c_row_cnt = "C" + std::to_string(cur_row + 1);
         wks_cur.cell(a_row_cnt).value() = cur_row;
         wks_cur.cell(b_row_cnt).value() = x;        

        //  std::string str_datetime = QDateTime::date()
        //  std::cout<< str_datetime <<std::endl;

        //  wks_cur.cell(c_row_cnt).value() = str_datetime.c_str();
         pDoc->save();
         pDoc->close();



    }catch(...)
    {

        std::cout<<"Open dataFile Fail"<<std::endl;

    }

    /******************************************************* */
        
}
