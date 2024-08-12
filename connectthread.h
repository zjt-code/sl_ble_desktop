#ifndef CONNECTTHREAD_H
#define CONNECTTHREAD_H
#include <QThread>
#include <vector>
#include <QMainWindow>
#include "simpleble/Adapter.h"
#include "simpleble/SimpleBLE.h"
#include <iostream>
#include <QProgressDialog>
#include <ctime>

typedef struct t_data_cgms
{
  uint8_t len;
  uint8_t flag;
  uint32_t offset;
  float   glucose;
  uint8_t history_flag;
  uint32_t trend;
  float   current;
  uint16_t quality;
  uint8_t status;
  uint8_t   cv;
 // uint8_t errorcode;
  
 // uint8_t countdown;

  
}T_CGMS_DATA;


static uint8_t crypte_state;

class ConnectThread : public QThread
{
    Q_OBJECT

public:
     bool isConnected=false,isruning = false;
     uint32_t cgms_offset;
     
     time_t tm_session_start;    // UTC timestample


     SimpleBLE::Peripheral peripheral_connected;

     //void(*pMeasCallback)(SimpleBLE::ByteArray& payload);


private:    
     static ConnectThread *pinternal;

public:


     ConnectThread(QObject *parent = nullptr);
     ~ConnectThread() override {
          isruning = false;
          pinternal->quit();
          pinternal->wait(); 
     }

     void run();
     void cgms_register_callback();
     uint8_t cgms_parse_status(void);
     void cgms_get_history_data(uint32_t &cgms_offset);
     void cgms_start_session(void);
     void cgms_send_sec_command(void);
     void cgms_set_pwd(void);
     uint8_t cgms_get_feature(void);
     time_t cgms_get_start_time(void);

     void cgms_update_key(void);
     void cgms_verify_pwd(void);
     void cgms_set_calibration(int g);
     

     static uint8_t cgms_meas_parse(uint8_t *data,T_CGMS_DATA &cgms_data);

     
     
     static void measurement_callback(SimpleBLE::ByteArray& payload);
     static void socp_callback(SimpleBLE::ByteArray &payload);
     static void status_callback(SimpleBLE::ByteArray &payload);
     static void racp_callback(SimpleBLE::ByteArray &payload);
     static void connected_callback(void);
     static void disconnected_callback(void);

signals:
     void SignalBleDebugInfo(std::string debuginfo);
     void SignalBleMeasNotify(std::vector <T_CGMS_DATA> payload);
     void SignalMeasureData(float x);
     
private:
     QProgressDialog *pProgressBar;  

};




#endif // CONNECTTHREAD_H
