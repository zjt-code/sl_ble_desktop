

#ifndef MYTHREAD_H
#define MYTHREAD_H


#include<iostream>
#include<QThread>
#include<QDebug>

class my_Thread : public QThread
{
     Q_OBJECT

protected:
    virtual void run()
    {

        
     while (1)          
            {
                //std::string abc;
                //abc="loops=" ;
                //emit SignalBleDebugInfo(abc);
                qDebug()<<"run()"<<QThread::currentThreadId();  

                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
         
    }


};

#endif