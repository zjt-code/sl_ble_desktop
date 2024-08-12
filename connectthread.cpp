


#include "connectthread.h"
#include "QDebug"
#include <chrono>
#include <iostream>
#include <thread>
#include <sstream>
#include <iomanip>
// #include "cgmsservice.h"
#include <QProgressBar>
#include  <QDateTime>

#include "user_service.h"
// #include  "aes.h"
// #include "cgms_crc.h"
// #include "mktime.h"

static uint8_t aes_ecb_128_key[16]={0x2B,0x7E,0x15,0x16,0x28,0xAE,0xD2,0xA6,0xAB,0xF7,0x15,0x88,0x09,0xCF,0xac,0xef};
static uint8_t password[2]={0x78,0x56};




std::string byte_array_to_string(SimpleBLE::ByteArray& bytes) {
    std::ostringstream oss;
    uint32_t len=0;

    for (auto byte : bytes) { len++;
        oss << std::hex << std::setfill('0') << std::setw(2) << (uint32_t)((uint8_t)byte) << " ";
    }

    oss<<" len="<<len;
    return oss.str();
}




ConnectThread *ConnectThread::pinternal =nullptr;

 ConnectThread::ConnectThread(QObject *parent) : QThread(parent)
{   
    isConnected=true;
    pinternal =this; 
    isruning = true;
    cgms_offset=0;
    crypte_state=0;
   // pProgressBar =new QProgressDialog();
    

}

void ConnectThread::connected_callback()
{
    qDebug()<<"connected success";;
    pinternal->SignalBleDebugInfo("connected success");

}

void ConnectThread::disconnected_callback()
{

    qDebug()<<"disconnected!!";
    pinternal->SignalBleDebugInfo("disconnected");

}


uint8_t ConnectThread::cgms_meas_parse(uint8_t *data, T_CGMS_DATA &cgms_data)
{
 

    return 0;
}
/*
data struct::
payload:
[0]: data len
[1]: Flag
[2:3]:glucose
[4:5]:measurement offset
[6]:running status
[7]:History Flag byte
[8]:error code
[9:10]:trend
[11:12]:quality
[13]:warmup count down
[14:15]:CRC
*/

 void ConnectThread::measurement_callback(SimpleBLE::ByteArray& payload)
{
      
        std::string outdata="Measurement ciper: " + byte_array_to_string(payload);
        //pinternal->SignalBleDebugInfo(outdata);
        int loop=0;

        std::cout<< outdata <<std::endl;

        int vol_value =0;

            
      
        for( char v : payload)
        {
            vol_value |= ((int)((uint8_t)v))<<(loop*8);
            loop++;
        }


       std::cout<<"vol: " << vol_value<<" mV" <<std::endl;
       std::cout<<"vol: " << (float)vol_value/100.0f<<" mV" <<std::endl;

        printf("%08x\r\n", vol_value);

    //    pinternal->SignalBleMeasNotify(cgmslist);   

        pinternal->SignalMeasureData((float)vol_value/100.0f);  

}


void ConnectThread::socp_callback(SimpleBLE::ByteArray &payload)
{

    std::ostringstream data,data2;

    uint8_t ciper_data[16];
    uint8_t lop=0;
 
    uint8_t plain_data[16]; 
 

}

void ConnectThread::status_callback(SimpleBLE::ByteArray &payload)
{
     std::string outdata="status: " + byte_array_to_string(payload);
     pinternal->SignalBleDebugInfo(outdata);

}

void ConnectThread::racp_callback(SimpleBLE::ByteArray &payload)
{

     std::cout<<"racp is callbacked"<<std::endl;
     std::string outdata="racp recv ciper->" + byte_array_to_string(payload);
     pinternal->SignalBleDebugInfo(outdata);

     std::ostringstream deciper_str;
     uint8_t ciper[16],loop=0,plain_data[16];

     for(uint8_t data:payload){ciper[loop++]=data;}      
        

   // AES128_ECB_decrypt(ciper,aes_ecb_128_key,plain_data);

    for(loop=0;loop<16;loop++)
    deciper_str<<" "<<std::hex<<std::setfill('0')<<std::setw(2)<<(uint32_t)plain_data[loop];
    
    pinternal->SignalBleDebugInfo("decipher racp->"+deciper_str.str());


}

void ConnectThread::cgms_register_callback()
{

      std::cout<<" register notify !!"<<std::endl;

      try
      {
        /* code */
        peripheral_connected.notify(USER_SERVICE_UUID,USER_SERVICE_NOTIFY_UUID,measurement_callback);

      }
      catch(const std::exception& e)
      {
        std::cerr << e.what() << '\n';
      }
      

    

    // peripheral_connected.notify(CGSM_SERVICE_UUID,CGMS_STATUS_CHAR_UUID,status_callback);

    // // std::cout<<"socp callbakc!!"<<std::endl;
    // peripheral_connected.notify(CGSM_SERVICE_UUID,CGMS_SOCP_CHAR_UUID,socp_callback);

    // peripheral_connected.notify(CGSM_SERVICE_UUID,CGMS_RACP_CHAR_UUID,racp_callback);

}

uint8_t ConnectThread::cgms_parse_status(void)
{
    std::ostringstream data;

    uint8_t loop=0,status;      

    return 0;

}

void ConnectThread::cgms_get_history_data(uint32_t &cgms_offset)
{
    uint8_t pchar[16] ={0x01,0x00,0x00,0x00,0x00,0x02,0x00};
    uint8_t ciper[16];
    uint32_t len=4;
    

    SimpleBLE::ByteArray byte_racp_cmd;
    byte_racp_cmd.clear();

  
    pchar[len++]=(uint8_t)cgms_offset;
    pchar[len++]=(uint8_t)(cgms_offset>>8);

    // uint16_t crc_v=do_crc(pchar,len);
    // pchar[len++]=uint8_t(crc_v);
    // pchar[len++]=uint8_t(crc_v>>8);

    
    // mbedtls_aes_pkcspadding(pchar,len);    
    // AES128_ECB_encrypt(pchar,aes_ecb_128_key,ciper);

    // // uint8_t cipher3[16]={0X3a,0X0f,0X17,0X04,0Xbb,0X1c,0Xb4,0Xe5,0Xe7,0X79,0X08,0Xfe,0X1b,0Xe8,0X5d,0x55};

    // for(uint8_t i=0;i<16;i++) byte_racp_cmd.push_back(ciper[i]);
    // std::cout<<"data len:"<<byte_racp_cmd.length()<<"racp cmd:"<<byte_array_to_string(byte_racp_cmd);

    // peripheral_connected.write_request(CGSM_SERVICE_UUID,CGMS_RACP_CHAR_UUID,byte_racp_cmd);

}

void ConnectThread::cgms_start_session(void)
{
        // time_t sec= time(nullptr);
        // tm  *tm_local = localtime( &sec);


        // qDebug()<<"Datetime:"<<tm_local->tm_year<<tm_local->tm_mon<<tm_local->tm_mday;

        // qDebug()<<"Datetime:"<<tm_local->tm_hour<<tm_local->tm_min<<tm_local->tm_sec;

        // uint8_t pchar[16]={SOCP_START_SESSION};
        // uint8_t len=1;


        // //add utc time
        // pchar[len++]=(uint8_t)sec;
        // pchar[len++]=(uint8_t)(sec>>8);
        // pchar[len++]=(uint8_t)(sec>>16);
        // pchar[len++]=(uint8_t)(sec>>24);
    
        // // add factor code
        // pchar[len++]=(uint8_t)(FACTORY_CODE);
        // pchar[len++]=(uint8_t)(FACTORY_CODE>>8);

        // //TimeZone
        // pchar[len++]=0;
        // //reserved
        // pchar[len++]=0;

        // //add startby
        // pchar[len++]=3;
        // //add start by version
        // pchar[len++]=1;
        // pchar[len++]=2;
        // pchar[len++]=4;
    
        // uint16_t crc_v=do_crc(pchar,len);
        // pchar[len++]=(uint8_t)crc_v;
        // pchar[len++]=(uint8_t)(crc_v>>8);
    
        // uint8_t cipher[16];
        // // encrypt
        // AES128_ECB_encrypt(pchar,aes_ecb_128_key,cipher);

        // std::ostringstream ssout;
        // SimpleBLE::ByteArray byte_socp_cmd;

        // for(int loo=0;loo<16;loo++)
        // {
        //     ssout<<std::hex<<std::setfill('0')<<std::setw(2)<<(uint32_t)cipher[loo]<<" ";
        //     byte_socp_cmd.push_back(cipher[loo]);
        // }

        // std::cout<<ssout.str()<<std::endl;
        // peripheral_connected.write_request(CGSM_SERVICE_UUID,CGMS_SOCP_CHAR_UUID,byte_socp_cmd);


}
void ConnectThread::cgms_send_sec_command()
{

    //   uint8_t pchar[16]={0x70,0x01,0x03};
    //   SimpleBLE::ByteArray byte_socp_cmd;

    //   for(int loo=0;loo<3;loo++)
    //   {
    //  // ssout<<std::hex<<std::setfill('0')<<std::setw(2)<<(uint32_t)pchar[loo]<<" ";
    //   byte_socp_cmd.push_back(pchar[loo]);
    //   }

    //   peripheral_connected.write_request(CGSM_SERVICE_UUID,CGMS_SOCP_CHAR_UUID,byte_socp_cmd);


}

uint8_t ConnectThread::cgms_get_feature(void)
{

    // uint8_t par_data[16],loop=0;

    // std::ostringstream str_data;


    // SimpleBLE::ByteArray data_arry =peripheral_connected.read(CGSM_SERVICE_UUID,CGMS_Feature_CHAR_UUID);

    // for(uint8_t data:data_arry)
    // {
    //     par_data[loop++]=data;
    //     str_data<<" "<<std::hex << std::setfill('0') << std::setw(2)<<(uint32_t)data;
    // }

    // std::cout<<"Feature"<<str_data.str()<<std::endl;

    // pinternal->SignalBleDebugInfo("Feature:"+str_data.str());

    // //Password set or not
    // if(par_data[4]&0x01)
    //     return 1;
    // else
    //     return 0;


    return 0;

}

void ConnectThread::cgms_set_pwd(void)
{
    // uint8_t cmd_plain[16]={0x78,0x56};
    // uint8_t cmd_cipler[16];
    // SimpleBLE::ByteArray byte_socp_cmd;
    // uint8_t loop=2;

    // std::cout<<"set cmd!!!!"<<std::endl;

    // cmd_plain[0]=password[0];
    // cmd_plain[1]=password[1];

    // for(uint8_t c:peripheral_connected.identifier())cmd_plain[loop++]=c;

    // cmd_plain[loop]=' ';

    // AES128_ECB_encrypt(cmd_plain,aes_ecb_128_key,cmd_cipler);


    // byte_socp_cmd.push_back(SOCP_SET_PWD);
    // for(uint8_t i=0;i<16;i++)byte_socp_cmd.push_back(cmd_cipler[i]);

    // peripheral_connected.write_request(CGSM_SERVICE_UUID,CGMS_SOCP_CHAR_UUID,byte_socp_cmd);


}


void ConnectThread::cgms_update_key()
{

    aes_ecb_128_key[14]=password[1];
    aes_ecb_128_key[15]=password[0];

}


void ConnectThread::cgms_set_calibration(int g)
{

    // uint8_t  cmd_plain[16]={SOCP_SET_CALIBRAION};
    // uint8_t  cmd_cipler[16];
    // uint8_t  len=1;

    // SimpleBLE::ByteArray byte_socp_cmd;    

    // //set gluecose
    // cmd_plain[len++]=(g>>0)&0xff;
    // cmd_plain[len++]=(g>>8)&0xff;

    // // set current offset
    // cmd_plain[len++]=(cgms_offset>>0)&0xff;
    // cmd_plain[len++]=(cgms_offset>>8)&0xff;

    // uint16_t crc_v= do_crc(cmd_plain,len);

    // cmd_plain[len++]=(crc_v>>0)&0xff;
    // cmd_plain[len++]=(crc_v>>8)&0xff;

    // for(int x=0; x< len; x++)printf("0x%02x-",cmd_plain[x]);

    // printf("\r\n");
     
    // AES128_ECB_encrypt(cmd_plain,aes_ecb_128_key,cmd_cipler);

    // for(uint8_t i=0;i<16;i++)byte_socp_cmd.push_back(cmd_cipler[i]);

    // peripheral_connected.write_request(CGSM_SERVICE_UUID,CGMS_SOCP_CHAR_UUID,byte_socp_cmd);

}

void ConnectThread::cgms_verify_pwd()
{

    // uint8_t cmd_plain[16]={SOCP_VERIFY_PWD,0x00};
    // uint8_t cmd_cipler[16];
    // uint8_t len=2;

    // SimpleBLE::ByteArray byte_socp_cmd;    

    // cmd_plain[len++]=password[0];
    // cmd_plain[len++]=password[1];

    // uint16_t crc_v= do_crc(cmd_plain,len);

    // cmd_plain[len++]=(uint8_t)crc_v;
    // cmd_plain[len++]=(uint8_t)(crc_v>>8);

    // AES128_ECB_encrypt(cmd_plain,aes_ecb_128_key,cmd_cipler);

    // for(uint8_t i=0;i<16;i++)byte_socp_cmd.push_back(cmd_cipler[i]);

    // peripheral_connected.write_request(CGSM_SERVICE_UUID,CGMS_SOCP_CHAR_UUID,byte_socp_cmd);



}


time_t ConnectThread::cgms_get_start_time(void)
{
 

    return 0;
}

void ConnectThread::run()
{
        uint8_t run_step=0;
        isConnected = true;
        isruning = true;

        // std::cout<<"runing "<<std::endl;


        // // SignalBleDebugInfo( "connect name:"+peripheral_connected.identifier()+
        // //          " addr:" + peripheral_connected.address());
         try
        {
                 peripheral_connected.set_callback_on_connected(connected_callback);

                peripheral_connected.set_callback_on_disconnected(disconnected_callback);

       
            /* code */
                peripheral_connected.connect();
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
        
        // //Can't find filter element
        std::cout << "Successfully connected, listing services." << std::endl;
        for (auto service : peripheral_connected.services())
        {
            std::cout<< "Service: " + service.uuid<<std::endl;

            for (auto characteristic : service.characteristics) {
                std::ostringstream ab;
                ab<<"  Characteristic: " << characteristic
                <<" prop: "<<std::hex<<std::setfill('0')<<std::setw(8)<<peripheral_connected.get_characteristic_prop(service.uuid,characteristic)
                ;
                std::cout<< ab.str()<<std::endl;

                // SignalBleDebugInfo(ab.str());

            }

        }

        //     /************read device info*********************/
        //              //auto readarray =peripheral.read("0000180a-0000-1000-8000-00805f9b34fb"," 00002a28-0000-1000-8000-00805f9b34fb");
        //      for (auto service : peripheral_connected.services())
        //      for (auto characteristic : service.characteristics)
        //      if(service.uuid.compare("0000180a-0000-1000-8000-00805f9b34fb")==0)
        //       {
        //          auto readdata=  peripheral_connected.read(service.uuid, characteristic);
        //          std::ostringstream ss;

        //          ss<<"read len:"<<readdata.length()<<" str:"<<readdata.c_str();
        //         //  pinternal->SignalBleDebugInfo(ss.str());

        //           std::cout<< ss.str()<<std::endl;
        //       }
          

    // // /*********************************************************************/
                
                cgms_register_callback();
            
    //          if(cgms_get_feature())
    //          {
    //              emit SignalBleDebugInfo("Password has been set!!");
    //              cgms_update_key();
    //          }
    //          else
    //          {
    //             emit SignalBleDebugInfo("Setting Password!!!");
    //             cgms_set_pwd();
    //             run_step =1;
    //          }     
         
            while(isConnected && isruning)
            {
                //std::string abc;
                //abc="loops=" ;
                //emit SignalBleDebugInfo(abc);
                //qDebug()<<"run()"<<QThread::currentThreadId();  

                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }

            
}
