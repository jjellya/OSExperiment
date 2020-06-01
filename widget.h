#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "uniprocessorsystem.h"
#include <QThread>
#include <QDebug>
#include <QMutex>
#include <cstdlib>

static QMutex myMutex;
static int num_test =0;


class CreateProcessThread:public QThread{
public:
       CreateProcessThread(QWidget *parent = nullptr){}
       ~CreateProcessThread(){}


       UniprocessorSystem *computer_SRT;
       UniprocessorSystem *computer_SPN;
       UniprocessorSystem *computer_DP;
       UniprocessorSystem *computer_RR;
       void init(UniprocessorSystem *computer_SRT,UniprocessorSystem *computer_SPN,UniprocessorSystem *computer_DP,UniprocessorSystem *computer_RR){//初始化后再放进来！
           this->computer_SRT = computer_SRT;
           this->computer_SPN = computer_SPN;
           this->computer_DP = computer_DP;
           this->computer_RR = computer_RR;
       }

       void run(){
           /**微秒级的精度时间作为时间种子**/
           LARGE_INTEGER nFrequency;
           if(::QueryPerformanceFrequency(&nFrequency))

             {

             LARGE_INTEGER nStartCounter;

             ::QueryPerformanceCounter(&nStartCounter);

             ::srand((unsigned)nStartCounter.LowPart);

             }
            UniqueCodeUtil randUtil;
            int nameCode = randUtil.getNameCode();
            int priCode = randUtil.getPriCode();
            int timeCode = randUtil.getTimeCode();

            computer_RR->createProcess(nameCode,priCode,timeCode);
            computer_DP->createProcess(nameCode,priCode,timeCode);
            computer_SPN->createProcess(nameCode,priCode,timeCode);
            computer_SRT->createProcess(nameCode,priCode,timeCode);

       }
};

class Create10ProcessThread:public QThread{
public:
       Create10ProcessThread(QWidget *parent = nullptr){}
       ~Create10ProcessThread(){}


       UniprocessorSystem *computer_SRT;
       UniprocessorSystem *computer_SPN;
       UniprocessorSystem *computer_DP;
       UniprocessorSystem *computer_RR;
       void init(UniprocessorSystem *computer_SRT,UniprocessorSystem *computer_SPN,UniprocessorSystem *computer_DP,UniprocessorSystem *computer_RR){//初始化后再放进来！
           this->computer_SRT = computer_SRT;
           this->computer_SPN = computer_SPN;
           this->computer_DP = computer_DP;
           this->computer_RR = computer_RR;
       }

       void run(){
           /**微秒级的精度时间作为时间种子**/
           LARGE_INTEGER nFrequency;
           if(::QueryPerformanceFrequency(&nFrequency))

             {

             LARGE_INTEGER nStartCounter;

             ::QueryPerformanceCounter(&nStartCounter);

             ::srand((unsigned)nStartCounter.LowPart);

             }


            UniqueCodeUtil randUtil;


            for(int i=0;i<10;i++){
                int nameCode = randUtil.getNameCode();
                int priCode = randUtil.getPriCode();
                int timeCode = randUtil.getTimeCode();

                computer_RR->createProcess(nameCode,priCode,timeCode);
                computer_DP->createProcess(nameCode,priCode,timeCode);
                computer_SPN->createProcess(nameCode,priCode,timeCode);
                computer_SRT->createProcess(nameCode,priCode,timeCode);
            }
       }
};


class DispatchThreadKIND:public QThread{
public:
       DispatchThreadKIND(QWidget *parent = nullptr){}
       ~DispatchThreadKIND(){}

       UniprocessorSystem *computer_KIND;
       //初始化后再放进来！
       void init(UniprocessorSystem *computer_KIND){
           this->computer_KIND = computer_KIND;
       }

       void run(){
           while(computer_KIND->getAvaiable()<10){              
                computer_KIND->dispatch();             
           }
       }
};


class DispatchThread:public QThread{
public:
       DispatchThread(QWidget *parent = nullptr){}
       ~DispatchThread(){}

       UniprocessorSystem *computer_SRT;
       UniprocessorSystem *computer_SPN;
       UniprocessorSystem *computer_DP;
       UniprocessorSystem *computer_RR;

       DispatchThreadKIND *dispatch_SRT;
       DispatchThreadKIND *dispatch_SPN;
       DispatchThreadKIND *dispatch_DP;
       DispatchThreadKIND *dispatch_RR;
       //初始化后再放进来！
       void init(UniprocessorSystem *computer_SRT,UniprocessorSystem *computer_SPN,UniprocessorSystem *computer_DP,UniprocessorSystem *computer_RR){
             dispatch_SRT= new DispatchThreadKIND;
             dispatch_SPN= new DispatchThreadKIND;
             dispatch_DP= new DispatchThreadKIND;
             dispatch_RR= new DispatchThreadKIND;

             dispatch_SRT->init(computer_SRT);
             dispatch_SPN->init(computer_SPN);
             dispatch_DP->init(computer_DP);
             dispatch_RR->init(computer_RR);
       }

       void run(){
           dispatch_RR->start();
           dispatch_DP->start();
           dispatch_SPN->start();
           dispatch_SRT->start();
       }
};



QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void Slots_setRunProgress(int pos,int range,int num);
    void Slots_setTextEditInt(int name,int num);


    void Slots_setReady1ProgressRR(int pos,int range,int num);
    void Slots_setReady1ProgressDP(int pos,int range,int num);
    void Slots_setReady1ProgressSPN(int pos,int range,int num);
    void Slots_setReady1ProgressSRT(int pos,int range,int num);

    void Slots_setReadyTextEditDP(int name,int num);
    void Slots_setReadyTextEditRR(int name,int num);
    void Slots_setReadyTextEditSPN(int name,int num);
    void Slots_setReadyTextEditSRT(int name,int num);

    void Slots_setTextEditAvgTime(double time,int num);



private slots:
    void on_pushButton_Dispatch_clicked();

    void on_pushButton_CreateProcess_clicked();



    void on_pushButton_clicked();

private:
    Ui::Widget *ui;
    UniprocessorSystem *computer_RR;
    UniprocessorSystem *computer_DP;
    UniprocessorSystem *computer_SPN;
    UniprocessorSystem *computer_SRT;

    CreateProcessThread *thCreate;
    Create10ProcessThread *thCreate10;
    DispatchThread *thDispatch;
};
#endif // WIDGET_H
