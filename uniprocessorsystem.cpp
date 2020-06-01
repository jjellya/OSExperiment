#include "uniprocessorsystem.h"
#include "QtDebug"
#include <time.h>
#include <stdio.h>
#include <windows.h>


int timeslice_num=0;

UniprocessorSystem::UniprocessorSystem(QObject *parent) : QObject(parent)
{

}

void UniprocessorSystem::showReadyQueue(){
    for(int i=0;i<2;i++)
                qDebug("\n");
            //pcbArea.showArea();
            Pcb p=readyQueue.head;
            while(p!=NULL){
                PCB s=*p;
                qDebug("p.name = %d, p.pri = %d, p.time = %d\n",p->name,p->pri,p->time);
                p=p->next;

            }
            qDebug("================CPU一共运行了%d个时间片================\n",timeslice_num);

}

void UniprocessorSystem::init(int mode){
    /*pFree = pcbArea.getPcbAreaByIndex(0);*/
            readyQueue.head=NULL;
            readyQueue.tail=readyQueue.head;
            run=NULL;
            this->mode = mode;
            available=N;
            for(int i=0;i<N;i++){
                this->pcbArea[i].name=UNUSED;

                if(i<N-1){
                    this->pcbArea[i].next=&pcbArea[i+1];
                }else{
                    this->pcbArea[i].next=NULL;
                }
                this->pcbArea[i].pri=0;
                this->pcbArea[i].status=END_STATUS;
                this->pcbArea[i].time=0;
            }
            pFree = &pcbArea[0];
}

void UniprocessorSystem::setIntoReadyQueue(READY &readyQueue,Pcb &target){
    if(mode==FCFS){
                //FCFS就绪队列放置方式
                if(readyQueue.head==NULL){
                    readyQueue.head=target;
                    readyQueue.tail=readyQueue.head;
                }else{
                    readyQueue.tail->next=target;
                    readyQueue.tail=readyQueue.tail->next;
                }
            }
            else if(mode==RR){
                //时间片轮转就绪队列放置方式,和FCFS几乎一样;
                if(readyQueue.head==NULL){
                    readyQueue.head=target;
                    readyQueue.tail=readyQueue.head;
                }else{
                    /*readyQueue.tail->next=target;
                    readyQueue.tail=readyQueue.tail->next;*/
                    target->next=readyQueue.head;
                    readyQueue.head=target;
                }
            }
            else if(mode==DP){
                //动态优先数调度就绪队列排列方式,维护一个优先级降序队列;
                if(readyQueue.head==NULL){
                    readyQueue.head=target;
                    readyQueue.tail=readyQueue.head;
                }
                else{
                    if(target->pri > readyQueue.head->pri){
                        target->next=readyQueue.head;
                        readyQueue.head=target;
                    }
                    else{
                        Pcb s,pre;
                        pre = readyQueue.head;
                        s = pre->next;
                        while(s!=NULL){
                            if(s->pri > target->pri){
                                pre=pre->next;
                                s=pre->next;
                            }
                            else{
                                break;
                            }
                        }
                        target->next = pre->next;
                        pre->next = target;
                    }
                    if(readyQueue.tail->next!=NULL)
                        readyQueue.tail=readyQueue.tail->next;
                }
            }
            else if(mode==SPN){
                //最短进程优先调度就绪队列放置,维护一个时间升序队列
                if(readyQueue.head==NULL){
                    readyQueue.head=target;
                    readyQueue.tail=readyQueue.head;
                }
                else{
                    if(target->time < readyQueue.head->time&&readyQueue.head->time==readyQueue.head->needTime){
                        target->next=readyQueue.head;
                        readyQueue.head=target;
                    }
                    else if(target->time < readyQueue.head->time&&readyQueue.head->time!=readyQueue.head->needTime){
                        target->next=readyQueue.head->next;
                        readyQueue.head->next=target;
                    }
                    else{
                        Pcb s,pre;
                        pre = readyQueue.head;
                        s = pre->next;
                        while(s!=NULL){
                            if(s->time <= target->time){
                                pre=pre->next;
                                s=pre->next;
                            }
                            else{
                                break;
                            }
                        }
                        target->next = pre->next;
                        pre->next = target;
                    }


                    if(readyQueue.tail->next!=NULL)
                        readyQueue.tail=readyQueue.tail->next;
                }
            }
            else if(mode==SRT){
                //最短剩余时间优先调度就绪队列放置,维护一个时间升序队列
                if(target->time>0){

                    if(readyQueue.head==NULL){
                        readyQueue.head=target;
                        readyQueue.tail=readyQueue.head;
                    }
                    else{
                        if(target->time < readyQueue.head->time){
                            target->next=readyQueue.head;
                            readyQueue.head=target;
                        }else{
                            Pcb s,pre;
                            pre = readyQueue.head;
                            s = pre->next;
                            PCB debugP=*pre;
                            while(s!=NULL){
                                if(s->time < target->time){
                                    pre=pre->next;
                                    s=pre->next;
                                }
                                else{
                                    break;
                                }
                            }
                            target->next = pre->next;
                            pre->next = target;
                        }

                        if(readyQueue.tail->next!=NULL)
                            readyQueue.tail=readyQueue.tail->next;
                    }

                }
                else{
                    printf("非法PCB插入!");
                }
            }
}


Pcb UniprocessorSystem::createPCB(int nameCode,int priCode,int timeCode){
    Pcb target = NULL;
            //若有空闲进程控制块,则可创建
            if(available>0&&pFree!=NULL) {
                target=pFree;
                pFree=pFree->next;
                available-=1;
                target->name = nameCode;
                target->pri = priCode;
                target->status = READY_STATUS;
                target->time = timeCode;
                target->needTime = target->time;
                target->next=NULL;
                target->start=clock();
                setIntoReadyQueue(readyQueue,target);
            }
            return target;
}

void  UniprocessorSystem::createProcess(int nameCode,int priCode,int timeCode){
    createPCB(nameCode,priCode,timeCode);//First;
    //Other Work...(恢复现场,继续运行之前的进程)
}

void UniprocessorSystem::runProcess(){
        run->time-=TIMESLICE;
        run->status=RUN_STATUS;
        run->next=NULL;

}

void UniprocessorSystem::releasePCB(Pcb &s){
        s->name=-1;
        s->pri = 0;
        s->status=END_STATUS;
        s->time=0;
        s->next=pFree;
        pFree=s;
        available+=1;
        s->end=clock();
        handleProcess_num++;
        sumTime+=s->end-s->start;
}

void UniprocessorSystem::dispatch(){
        if(readyQueue.head==NULL) {printf("[Error]:Current ready queue has not context!\n"); return;}
        if(mode==RR){

            if(readyQueue.head!=NULL){
                run=readyQueue.head;
                 emit setTextEditInt(run->name,mode);
                Pcb readyNext=readyQueue.head->next;

                timeslice_num++;

                showReadyQueue();

                runProcess();
                emit setRunProgress(run->needTime-run->time,run->needTime,mode);

                //TODO CPU cpu1.run();

                READY  temp;
                temp.head=readyNext;temp.tail=readyQueue.tail;

                Pcb p=temp.head;
                int flag[11]={0,0,0,0,0,0,0,0,0,0,0};
                int queue_i=1;
                    while(p!=NULL){
                        //qDebug("p.name = %d, p.pri = %d, p.time = %d\n",p->name,p->pri,p->time);
                        if(flag[queue_i]==0){
                            qDebug("ReadyQueue_%d, ReadyProcess.name = %d\n",queue_i,p->name);
                            emit setReadyTextEditRR(p->name,queue_i);
                            emit setReady1ProgressRR(p->needTime-p->time,p->needTime,queue_i);
                            flag[queue_i]=1;
                            queue_i++;
                        }
                        p=p->next;

                    }

                if(run->time>0){
                    run->status=READY_STATUS;
                    if(readyQueue.tail!=run){
                        readyQueue.tail->next=run;
                        readyQueue.tail=run;
                    } //else：如果 readyQueue.tail==run,则只剩下一个进程就是run本身独享CPU

                    if(readyNext==NULL)
                        readyNext=run;
                } else{
                    releasePCB(run);
                    queue_i--;
                    emit setReadyTextEditRR(-1,queue_i);
                    emit setReady1ProgressRR(0,100,queue_i);
                }
                //pcbArea.setPcbArea(run,run);
                //Attenetion:Next one row may be cause a bug.
                readyQueue.head=readyNext;
                if(handleProcess_num>0)
                emit setTextEditAvgTime(sumTime*1.000000/handleProcess_num/1000,mode);
                Sleep(300);
            }
        }
        else if(mode==DP){
            if(readyQueue.head!=NULL){
                run=readyQueue.head;
                emit setTextEditInt(run->name,mode);
                Pcb readyNext=readyQueue.head->next;

                timeslice_num++;

                showReadyQueue();
                //被调度时执行：优先数－1，剩余运行时间－1.
                runProcess();
                run->pri-=1;
                emit setRunProgress(run->needTime-run->time,run->needTime,mode);

                //TODO CPU cpu1.run();
                READY  temp;
                temp.head=readyNext;temp.tail=readyQueue.tail;

                Pcb p=temp.head;
                int flag[11]={0,0,0,0,0,0,0,0,0,0,0};
                int queue_i=1;
                    while(p!=NULL){
                        //qDebug("p.name = %d, p.pri = %d, p.time = %d\n",p->name,p->pri,p->time);
                        if(flag[queue_i]==0){
                            qDebug("ReadyQueue_%d, ReadyProcess.name = %d\n",queue_i,p->name);
                            emit setReadyTextEditDP(p->name,queue_i);
                            emit setReady1ProgressDP(p->needTime-p->time,p->needTime,queue_i);
                            flag[queue_i]=1;
                            queue_i++;
                        }
                        p=p->next;

                    }

                if(run->time>0){
                    run->status=READY_STATUS;
                    if(readyQueue.tail!=run){
                        setIntoReadyQueue(temp,run);
                    } //else: 如果 readyQueue.tail==run,则只剩下一个进程就是run本身独享CPU
                    if(temp.head==NULL){
                        temp.head=run;
                    }
                } else{
                    releasePCB(run);
                    queue_i--;
                    emit setReadyTextEditDP(-1,queue_i);
                    emit setReady1ProgressDP(0,100,queue_i);
                }
               // pcbArea.setPcbArea(run,run);
                //Attenetion:Next one row may be cause a bug.
                readyQueue.head=temp.head;
                readyQueue.tail=temp.tail;
                emit setTextEditAvgTime(sumTime*1.000000/handleProcess_num/1000,mode);
                Sleep(300);

            }
        }
        else if(mode==SPN){
            if(readyQueue.head!=NULL){
                run=readyQueue.head;
                emit setTextEditInt(run->name,mode);
                emit setRunProgress(run->needTime-run->time,run->needTime,mode);
                Pcb readyNext=readyQueue.head->next;

                timeslice_num++;

                showReadyQueue();

                 runProcess();
                 emit setRunProgress(run->needTime-run->time,run->needTime,mode);

                //TODO CPU cpu1.run();
                READY  temp;
                temp.head=readyNext;temp.tail=readyQueue.tail;

                Pcb p=temp.head;
                int flag[11]={0,0,0,0,0,0,0,0,0,0,0};
                int queue_i=1;
                    while(p!=NULL){
                        if(flag[queue_i]==0){
                            qDebug("ReadyQueue_%d, ReadyProcess.name = %d\n",queue_i,p->name);
                            emit setReadyTextEditSPN(p->name,queue_i);
                            emit setReady1ProgressSPN(p->needTime-p->time,p->needTime,queue_i);
                            flag[queue_i]=1;
                            queue_i++;
                        }
                        p=p->next;

                    }
//                while (run->time>0){
//                    runProcess();
//                    Sleep(300);
//                    emit setRunProgress(run->needTime-run->time,run->needTime,mode);
//                }

                if(run->time>0){
                    run->status=READY_STATUS;
                    run->next=temp.head;
                    temp.head=run;
                }
                else{
                    releasePCB(run);
                    if(readyNext!=NULL) queue_i--;
                    emit setReadyTextEditSPN(-1,queue_i);
                    emit setReady1ProgressSPN(0,100,queue_i);
                }
                //Attenetion:Next one row may be cause a bug.
                readyQueue.head=temp.head;
                readyQueue.tail=temp.tail;
                emit setTextEditAvgTime(sumTime*1.000000/handleProcess_num/1000,mode);
                Sleep(300);
            }
        }
        else if(mode==SRT){
            if(readyQueue.head!=NULL){
                run=readyQueue.head;
                 emit setTextEditInt(run->name,mode);
                Pcb readyNext=readyQueue.head->next;

                timeslice_num++;

                showReadyQueue();

                runProcess();
                emit setRunProgress(run->needTime-run->time,run->needTime,mode);

                //TODO CPU cpu1.run();
                READY  temp;
                temp.head=readyNext;temp.tail=readyQueue.tail;

                Pcb p=temp.head;
                int flag[11]={0,0,0,0,0,0,0,0,0,0,0};
                int queue_i=1;
                    while(p!=NULL){
                        if(flag[queue_i]==0){
                            qDebug("ReadyQueue_%d, ReadyProcess.name = %d\n",queue_i,p->name);
                            emit setReadyTextEditSRT(p->name,queue_i);
                            emit setReady1ProgressSRT(p->needTime-p->time,p->needTime,queue_i);
                            flag[queue_i]=1;
                            queue_i++;
                        }
                        p=p->next;

                    }

                if(run->time>0){
                    run->status=READY_STATUS;
                    if(readyQueue.tail!=run){
                        setIntoReadyQueue(temp,run);
                    } //else: 如果 readyQueue.tail==run,则只剩下一个进程就是run本身独享CPU
                    if(temp.head==NULL){
                        temp.head=run;
                    }
                } else{
                    releasePCB(run);
                    queue_i--;
                    emit setReadyTextEditSRT(-1,queue_i);
                    emit setReady1ProgressSRT(0,100,queue_i);
                }
                //Attenetion:Next one row may be cause a bug.
                readyQueue.head=temp.head;
                readyQueue.tail=temp.tail;
                emit setTextEditAvgTime(sumTime*1.000000/handleProcess_num/1000,mode);
                Sleep(300);
            }
        }
}


void UniprocessorSystem::setReadyQueue(READY readyQueue){
        //TODO:注意此处的this.readyQueue，是否需要new 一个实例
        this->readyQueue = readyQueue;
        this->readyQueue = readyQueue;
}

void UniprocessorSystem::setRun(Pcb run){
        //TODO:注意此处的this.run，是否需要new 一个实例
        this->run = run;
}

void UniprocessorSystem::setPFree(Pcb pFree){
        //TODO:注意此处的this.pFree，是否需要new 一个实例
        this->pFree = pFree;
}

READY UniprocessorSystem::getReadyQueue(){
        return this->readyQueue;
}

int UniprocessorSystem::getRun(){
            int result = -1;
            if (this->run != NULL) {
                result = this->run->name;
            }
            return result;
}

Pcb UniprocessorSystem::getPFree(){
        return this->pFree;
}

int UniprocessorSystem:: getAvaiable(){
        return available;
}
