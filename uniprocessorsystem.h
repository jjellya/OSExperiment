#ifndef UNIPROCESSORSYSTEM_H
#define UNIPROCESSORSYSTEM_H

#include <QObject>
#include<iostream>
#include<cstdio>
#include <cstdlib>
#include<algorithm>
#include<cmath>
#include<time.h>
#include<cstring>
#include<windows.h>
#define N 10          //假定系统允许进程个数为 N
#define TIMESLICE 1		//时间片暂定为 1
#define UNUSED -1
#define FCFS 100	//先来先服务
#define RR 101	//轮转
#define DP 102	//动态优先级
#define SPN 103	//最短进程优先
#define SRT	104	//最短剩余时间优先
using namespace std;

enum status {READY_STATUS,RUN_STATUS,END_STATUS}; // 定义枚举类型Status

typedef struct pcb{
    int name;	//PCB唯一标识符,它由操作系统分配的;
    int status;	//仅包含进程状态;
    int pri;	//进程优先数（赋予进程的优先数，调度时总是选取优先数大的进程先执行。）
    int time;	//剩余运行时间，以时间片为单位，当减至 0 时该进程终止
    int needTime;//整个进程需要的时间
    double start;//开始时间
    double end;  //结束时间
    struct pcb *next;	 //指向下一个进程控制块的位置
}PCB,*Pcb;



typedef struct ready{
    struct pcb *head; //定义指向就绪队列的头指针 head 和尾指针 tail
    struct pcb *tail;
}READY,*Ready;



class UniqueCodeUtil{

    int nameCode;
    int priCode;
    int timeCode;

public:

    int getNameCode(){

        this->nameCode=rand()%10000+1;//自动编号;
        return nameCode;
    }

    int getPriCode(){
        this->priCode=rand()%64+20;//自动编号;
        return priCode;
    }

    int getTimeCode(){
        this->timeCode=rand()%20+1;//自动编号;
        return timeCode;
    }
};


class UniprocessorSystem : public QObject
{
    /*PcbArea pcbArea;*/
        struct pcb pcbArea[N];

        /**
        *以下指针分别定义了 就绪队列、处理器、等待队列;
        *
        **/
        READY readyQueue;

        //struct pcb *run;//定义指向正在运行进程的进程控制块的指针
        Pcb run;

        //struct pcb *pFree; //定义指向空闲进程控制块队列的指针
        Pcb pFree;

        int mode;

        int available;

        double sumTime=0;

        int handleProcess_num=0;

    Q_OBJECT
public:
    explicit UniprocessorSystem(QObject *parent = nullptr);

        void showReadyQueue();
        void init(int mode);
        void setIntoReadyQueue(READY &readyQueue,Pcb &target);
        Pcb createPCB(int nameCode,int priCode,int timeCode);
        void createProcess(int nameCode,int priCode,int timeCode);
        void runProcess();
        void releasePCB(Pcb &s);
        void dispatch();
        void setReadyQueue(READY readyQueue);
        void setRun(Pcb run);
        void setPFree(Pcb pFree);
        READY getReadyQueue();
        int getRun();
        Pcb getRunPointer();
        Pcb getPFree();
        int getAvaiable();
        int getMode();

signals:
    //自定义信号写到这里下面：
    void setRunProgress(int pos,int range,int num);
    void setTextEditInt(int name,int num);


    void setReady1ProgressRR(int pos,int range,int num);
    void setReady1ProgressDP(int pos,int range,int num);
    void setReady1ProgressSPN(int pos,int range,int num);
    void setReady1ProgressSRT(int pos,int range,int num);


     void setReadyTextEditRR(int name,int num);
     void setReadyTextEditDP(int name,int num);
     void setReadyTextEditSPN(int name,int num);
     void setReadyTextEditSRT(int name,int num);

     void setTextEditAvgTime(double time,int num);

     void setRunTextEditPri(int pri,int num);
     void setRunTextEditTime(int time,int num);

     void setReadyTextEditPriRR(int pri,int num);
     void setReadyTextEditPriDP(int pri,int num);
     void setReadyTextEditPriSPN(int pri,int num);
     void setReadyTextEditPriSRT(int pri,int num);


     void setReadyTextEditTimeRR(int time,int num);
     void setReadyTextEditTimeDP(int time,int num);
     void setReadyTextEditTimeSPN(int time,int num);
     void setReadyTextEditTimeSRT(int time,int num);


public slots:
};

#endif // UNIPROCESSORSYSTEM_H
