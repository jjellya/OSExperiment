#include "widget.h"
#include "ui_widget.h"
#include "QtDebug"
#include "uniprocessorsystem.h"
#include <QMessageBox>
#include <QThread>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    thCreate = new CreateProcessThread;
    thCreate10 = new Create10ProcessThread;
    thDispatch = new DispatchThread;

    ui->progressBar_Run_DP->setValue(0);
    ui->progressBar_Run_RR->setValue(0);
    ui->progressBar_Run_SPN->setValue(0);
    ui->progressBar_Run_SRT->setValue(0);

    ui->progressBar_Ready_DP1->setValue(0);
    ui->progressBar_Ready_DP2->setValue(0);
    ui->progressBar_Ready_DP3->setValue(0);
    ui->progressBar_Ready_DP4->setValue(0);
    ui->progressBar_Ready_DP5->setValue(0);
    ui->progressBar_Ready_DP6->setValue(0);
    ui->progressBar_Ready_DP7->setValue(0);
    ui->progressBar_Ready_DP8->setValue(0);
    ui->progressBar_Ready_DP9->setValue(0);


    ui->progressBar_Ready_RR1->setValue(0);
    ui->progressBar_Ready_RR2->setValue(0);
    ui->progressBar_Ready_RR3->setValue(0);
    ui->progressBar_Ready_RR4->setValue(0);
    ui->progressBar_Ready_RR5->setValue(0);
    ui->progressBar_Ready_RR6->setValue(0);
    ui->progressBar_Ready_RR7->setValue(0);
    ui->progressBar_Ready_RR8->setValue(0);
    ui->progressBar_Ready_RR9->setValue(0);

    ui->progressBar_Ready_SPN1->setValue(0);
    ui->progressBar_Ready_SPN2->setValue(0);
    ui->progressBar_Ready_SPN3->setValue(0);
    ui->progressBar_Ready_SPN4->setValue(0);
    ui->progressBar_Ready_SPN5->setValue(0);
    ui->progressBar_Ready_SPN6->setValue(0);
    ui->progressBar_Ready_SPN7->setValue(0);
    ui->progressBar_Ready_SPN8->setValue(0);
    ui->progressBar_Ready_SPN9->setValue(0);

    ui->progressBar_Ready_SRT1->setValue(0);
    ui->progressBar_Ready_SRT2->setValue(0);
    ui->progressBar_Ready_SRT3->setValue(0);
    ui->progressBar_Ready_SRT4->setValue(0);
    ui->progressBar_Ready_SRT5->setValue(0);
    ui->progressBar_Ready_SRT6->setValue(0);
    ui->progressBar_Ready_SRT7->setValue(0);
    ui->progressBar_Ready_SRT8->setValue(0);
    ui->progressBar_Ready_SRT9->setValue(0);

    ui->lineEdit_Run->setAlignment(Qt::AlignCenter);
    ui->lineEdit_Ready_DP1->setAlignment(Qt::AlignCenter);
    ui->lineEdit_Ready_DP2->setAlignment(Qt::AlignCenter);
    ui->lineEdit_Ready_DP3->setAlignment(Qt::AlignCenter);
    ui->lineEdit_Ready_DP4->setAlignment(Qt::AlignCenter);
    ui->lineEdit_Ready_DP5->setAlignment(Qt::AlignCenter);
    ui->lineEdit_Ready_DP6->setAlignment(Qt::AlignCenter);
    ui->lineEdit_Ready_DP7->setAlignment(Qt::AlignCenter);
    ui->lineEdit_Ready_DP8->setAlignment(Qt::AlignCenter);
    ui->lineEdit_Ready_DP9->setAlignment(Qt::AlignCenter);
    ui->textEdit->setAlignment(Qt::AlignCenter);

    this->computer_RR = new UniprocessorSystem(this);
    this->computer_DP = new UniprocessorSystem(this);
    this->computer_SPN = new UniprocessorSystem(this);
    this->computer_SRT = new UniprocessorSystem(this);

    this->computer_RR->init(RR);
    this->computer_DP->init(DP);
    this->computer_SPN->init(SPN);
    this->computer_SRT->init(SRT);

    thCreate->init(computer_SRT,computer_SPN,computer_DP,computer_RR);
    thCreate10->init(computer_SRT,computer_SPN,computer_DP,computer_RR);
    thDispatch->init(computer_SRT,computer_SPN,computer_DP,computer_RR);

    connect(computer_RR,&UniprocessorSystem::setRunProgress,this,&Widget::Slots_setRunProgress);
    connect(computer_DP,&UniprocessorSystem::setRunProgress,this,&Widget::Slots_setRunProgress);
    connect(computer_SPN,&UniprocessorSystem::setRunProgress,this,&Widget::Slots_setRunProgress);
    connect(computer_SRT,&UniprocessorSystem::setRunProgress,this,&Widget::Slots_setRunProgress);

    connect(computer_RR,&UniprocessorSystem::setTextEditInt,this,&Widget::Slots_setTextEditInt);
    connect(computer_DP,&UniprocessorSystem::setTextEditInt,this,&Widget::Slots_setTextEditInt);
    connect(computer_SPN,&UniprocessorSystem::setTextEditInt,this,&Widget::Slots_setTextEditInt);
    connect(computer_SRT,&UniprocessorSystem::setTextEditInt,this,&Widget::Slots_setTextEditInt);

    connect(computer_RR,&UniprocessorSystem::setReady1ProgressRR,this,&Widget::Slots_setReady1ProgressRR);
    connect(computer_DP,&UniprocessorSystem::setReady1ProgressDP,this,&Widget::Slots_setReady1ProgressDP);
    connect(computer_SPN,&UniprocessorSystem::setReady1ProgressSPN,this,&Widget::Slots_setReady1ProgressSPN);
    connect(computer_SRT,&UniprocessorSystem::setReady1ProgressSRT,this,&Widget::Slots_setReady1ProgressSRT);


    connect(computer_RR,&UniprocessorSystem::setReadyTextEditRR,this,&Widget::Slots_setReadyTextEditRR);
    connect(computer_DP,&UniprocessorSystem::setReadyTextEditDP,this,&Widget::Slots_setReadyTextEditDP);
    connect(computer_SPN,&UniprocessorSystem::setReadyTextEditSPN,this,&Widget::Slots_setReadyTextEditSPN);
    connect(computer_SRT,&UniprocessorSystem::setReadyTextEditSRT,this,&Widget::Slots_setReadyTextEditSRT);

    connect(computer_RR,&UniprocessorSystem::setTextEditAvgTime,this,&Widget::Slots_setTextEditAvgTime);
    connect(computer_DP,&UniprocessorSystem::setTextEditAvgTime,this,&Widget::Slots_setTextEditAvgTime);
    connect(computer_SPN,&UniprocessorSystem::setTextEditAvgTime,this,&Widget::Slots_setTextEditAvgTime);
    connect(computer_SRT,&UniprocessorSystem::setTextEditAvgTime,this,&Widget::Slots_setTextEditAvgTime);

    connect(computer_RR,&UniprocessorSystem::setRunTextEditPri,this,&Widget::Slots_setRunTextEditPri);
    connect(computer_DP,&UniprocessorSystem::setRunTextEditPri,this,&Widget::Slots_setRunTextEditPri);
    connect(computer_SPN,&UniprocessorSystem::setRunTextEditPri,this,&Widget::Slots_setRunTextEditPri);
    connect(computer_SRT,&UniprocessorSystem::setRunTextEditPri,this,&Widget::Slots_setRunTextEditPri);

    connect(computer_RR,&UniprocessorSystem::setRunTextEditTime,this,&Widget::Slots_setRunTextEditTime);
    connect(computer_DP,&UniprocessorSystem::setRunTextEditTime,this,&Widget::Slots_setRunTextEditTime);
    connect(computer_SPN,&UniprocessorSystem::setRunTextEditTime,this,&Widget::Slots_setRunTextEditTime);
    connect(computer_SRT,&UniprocessorSystem::setRunTextEditTime,this,&Widget::Slots_setRunTextEditTime);

    connect(computer_RR,&UniprocessorSystem::setReadyTextEditPriRR,this,&Widget::Slots_setReadyTextEditPriRR);
    connect(computer_DP,&UniprocessorSystem::setReadyTextEditPriDP,this,&Widget::Slots_setReadyTextEditPriDP);
    connect(computer_SPN,&UniprocessorSystem::setReadyTextEditPriSPN,this,&Widget::Slots_setReadyTextEditPriSPN);
    connect(computer_SRT,&UniprocessorSystem::setReadyTextEditPriSRT,this,&Widget::Slots_setReadyTextEditPriSRT);

    connect(computer_RR,&UniprocessorSystem::setReadyTextEditTimeRR,this,&Widget::Slots_setReadyTextEditTimeRR);
    connect(computer_DP,&UniprocessorSystem::setReadyTextEditTimeDP,this,&Widget::Slots_setReadyTextEditTimeDP);
    connect(computer_SPN,&UniprocessorSystem::setReadyTextEditTimeSPN,this,&Widget::Slots_setReadyTextEditTimeSPN);
    connect(computer_SRT,&UniprocessorSystem::setReadyTextEditTimeSRT,this,&Widget::Slots_setReadyTextEditTimeSRT);



}

Widget::~Widget()
{
    delete ui;
}


void Widget::Slots_setRunProgress(int pos, int range,int num){
    switch (num) {
        case RR:   ui->progressBar_Run_RR->setRange(0,range);
                    ui->progressBar_Run_RR->setValue(pos);
                    break;
        case DP:   ui->progressBar_Run_DP->setRange(0,range);
                    ui->progressBar_Run_DP->setValue(pos);
                    break;
        case SPN:   ui->progressBar_Run_SPN->setRange(0,range);
                    ui->progressBar_Run_SPN->setValue(pos);
                    break;
        case SRT:   ui->progressBar_Run_SRT->setRange(0,range);
                    ui->progressBar_Run_SRT->setValue(pos);
                    break;
        default:break;
    }

}

void Widget::on_pushButton_Dispatch_clicked()
{
    thDispatch->start();
}



void Widget::on_pushButton_CreateProcess_clicked()
{
    thCreate->start();
      QMessageBox::information(NULL, "Message", "Create Process Success\n");
}

void Widget::on_pushButton_clicked()
{
    thCreate10->start();
      QMessageBox::information(NULL, "Message", "Create 10 Process Success!\nHowever,the process can't be created if the current computer's the number of process more than 10.\n");
}

void Widget::Slots_setTextEditInt(int name,int num){
        string str1 = std::to_string(name);
        if(name==-1)
            str1="";
        QString qstr = QString::fromStdString(str1);
        switch (num) {
            case 101:   ui->lineEdit_Run_RR->setText(qstr);
                        break;
            case 102:   ui->lineEdit_Run->setText(qstr);
                        break;
            case 103:   ui->lineEdit_Run_SPN->setText(qstr);
                        break;
            case 104:   ui->lineEdit_Run_SRT->setText(qstr);
                        break;
            default:break;
        }

}

void Widget::Slots_setReady1ProgressRR(int pos,int range,int num){
    switch (num) {
        case 1: ui->progressBar_Ready_RR1->setRange(0,range);
                ui->progressBar_Ready_RR1->setValue(pos);
                break;
        case 2: ui->progressBar_Ready_RR2->setRange(0,range);
                ui->progressBar_Ready_RR2->setValue(pos);
                break;
        case 3: ui->progressBar_Ready_RR3->setRange(0,range);
                ui->progressBar_Ready_RR3->setValue(pos);
                break;
        case 4: ui->progressBar_Ready_RR4->setRange(0,range);
                ui->progressBar_Ready_RR4->setValue(pos);
                break;
        case 5: ui->progressBar_Ready_RR5->setRange(0,range);
                ui->progressBar_Ready_RR5->setValue(pos);
                break;
        case 6: ui->progressBar_Ready_RR6->setRange(0,range);
                ui->progressBar_Ready_RR6->setValue(pos);
                break;
        case 7: ui->progressBar_Ready_RR7->setRange(0,range);
                ui->progressBar_Ready_RR7->setValue(pos);
                break;
        case 8: ui->progressBar_Ready_RR8->setRange(0,range);
                ui->progressBar_Ready_RR8->setValue(pos);
                break;
        case 9: ui->progressBar_Ready_RR9->setRange(0,range);
                ui->progressBar_Ready_RR9->setValue(pos);
                break;
         default:break;

    }
 }


void Widget::Slots_setReady1ProgressDP(int pos,int range,int num){
    switch (num) {
        case 1: ui->progressBar_Ready_DP1->setRange(0,range);
                ui->progressBar_Ready_DP1->setValue(pos);
                break;
        case 2: ui->progressBar_Ready_DP2->setRange(0,range);
                ui->progressBar_Ready_DP2->setValue(pos);
                break;
        case 3: ui->progressBar_Ready_DP3->setRange(0,range);
                ui->progressBar_Ready_DP3->setValue(pos);
                break;
        case 4: ui->progressBar_Ready_DP4->setRange(0,range);
                ui->progressBar_Ready_DP4->setValue(pos);
                break;
        case 5: ui->progressBar_Ready_DP5->setRange(0,range);
                ui->progressBar_Ready_DP5->setValue(pos);
                break;
        case 6: ui->progressBar_Ready_DP6->setRange(0,range);
                ui->progressBar_Ready_DP6->setValue(pos);
                break;
        case 7: ui->progressBar_Ready_DP7->setRange(0,range);
                ui->progressBar_Ready_DP7->setValue(pos);
                break;
        case 8: ui->progressBar_Ready_DP8->setRange(0,range);
                ui->progressBar_Ready_DP8->setValue(pos);
                break;
        case 9: ui->progressBar_Ready_DP9->setRange(0,range);
                ui->progressBar_Ready_DP9->setValue(pos);
                break;
         default:break;

    }
 }

void Widget::Slots_setReady1ProgressSPN(int pos, int range, int num){
    switch (num) {
        case 1: ui->progressBar_Ready_SPN1->setRange(0,range);
                ui->progressBar_Ready_SPN1->setValue(pos);
                break;
        case 2: ui->progressBar_Ready_SPN2->setRange(0,range);
                ui->progressBar_Ready_SPN2->setValue(pos);
                break;
        case 3: ui->progressBar_Ready_SPN3->setRange(0,range);
                ui->progressBar_Ready_SPN3->setValue(pos);
                break;
        case 4: ui->progressBar_Ready_SPN4->setRange(0,range);
                ui->progressBar_Ready_SPN4->setValue(pos);
                break;
        case 5: ui->progressBar_Ready_SPN5->setRange(0,range);
                ui->progressBar_Ready_SPN5->setValue(pos);
                break;
        case 6: ui->progressBar_Ready_SPN6->setRange(0,range);
                ui->progressBar_Ready_SPN6->setValue(pos);
                break;
        case 7: ui->progressBar_Ready_SPN7->setRange(0,range);
                ui->progressBar_Ready_SPN7->setValue(pos);
                break;
        case 8: ui->progressBar_Ready_SPN8->setRange(0,range);
                ui->progressBar_Ready_SPN8->setValue(pos);
                break;
        case 9: ui->progressBar_Ready_SPN9->setRange(0,range);
                ui->progressBar_Ready_SPN9->setValue(pos);
                break;
         default:break;

    }
 }

void Widget::Slots_setReady1ProgressSRT(int pos, int range, int num){
    switch (num) {
        case 1: ui->progressBar_Ready_SRT1->setRange(0,range);
                ui->progressBar_Ready_SRT1->setValue(pos);
                break;
        case 2: ui->progressBar_Ready_SRT2->setRange(0,range);
                ui->progressBar_Ready_SRT2->setValue(pos);
                break;
        case 3: ui->progressBar_Ready_SRT3->setRange(0,range);
                ui->progressBar_Ready_SRT3->setValue(pos);
                break;
        case 4: ui->progressBar_Ready_SRT4->setRange(0,range);
                ui->progressBar_Ready_SRT4->setValue(pos);
                break;
        case 5: ui->progressBar_Ready_SRT5->setRange(0,range);
                ui->progressBar_Ready_SRT5->setValue(pos);
                break;
        case 6: ui->progressBar_Ready_SRT6->setRange(0,range);
                ui->progressBar_Ready_SRT6->setValue(pos);
                break;
        case 7: ui->progressBar_Ready_SRT7->setRange(0,range);
                ui->progressBar_Ready_SRT7->setValue(pos);
                break;
        case 8: ui->progressBar_Ready_SRT8->setRange(0,range);
                ui->progressBar_Ready_SRT8->setValue(pos);
                break;
        case 9: ui->progressBar_Ready_SRT9->setRange(0,range);
                ui->progressBar_Ready_SRT9->setValue(pos);
                break;
         default:break;

    }
 }

void Widget::Slots_setReadyTextEditRR(int name,int num){

    string str1 = std::to_string(name);
    if(name==-1)
        str1="";

    QString qstr = QString::fromStdString(str1);
//    ui->lineEdit_Run->setText(qstr);
    switch (num) {
        case 1: ui->lineEdit_Ready_RR1->setText(qstr);break;
        case 2: ui->lineEdit_Ready_RR2->setText(qstr);break;
        case 3: ui->lineEdit_Ready_RR3->setText(qstr);break;
        case 4: ui->lineEdit_Ready_RR4->setText(qstr);break;
        case 5: ui->lineEdit_Ready_RR5->setText(qstr);break;
        case 6: ui->lineEdit_Ready_RR6->setText(qstr);break;
        case 7: ui->lineEdit_Ready_RR7->setText(qstr);break;
        case 8: ui->lineEdit_Ready_RR8->setText(qstr);break;
        case 9: ui->lineEdit_Ready_RR9->setText(qstr);break;
        default:break;
    }
}


void Widget::Slots_setReadyTextEditDP(int name,int num){

    string str1 = std::to_string(name);
    if(name==-1)
        str1="";

    QString qstr = QString::fromStdString(str1);
//    ui->lineEdit_Run->setText(qstr);
    switch (num) {
        case 1: ui->lineEdit_Ready_DP1->setText(qstr);break;
        case 2: ui->lineEdit_Ready_DP2->setText(qstr);break;
        case 3: ui->lineEdit_Ready_DP3->setText(qstr);break;
        case 4: ui->lineEdit_Ready_DP4->setText(qstr);break;
        case 5: ui->lineEdit_Ready_DP5->setText(qstr);break;
        case 6: ui->lineEdit_Ready_DP6->setText(qstr);break;
        case 7: ui->lineEdit_Ready_DP7->setText(qstr);break;
        case 8: ui->lineEdit_Ready_DP8->setText(qstr);break;
        case 9: ui->lineEdit_Ready_DP9->setText(qstr);break;
        default:break;
    }
}

void Widget::Slots_setReadyTextEditSPN(int name, int num){

    string str1 = std::to_string(name);
    if(name==-1)
        str1="";
    QString qstr = QString::fromStdString(str1);
    switch (num) {
        case 1: ui->lineEdit_Ready_SPN1->setText(qstr);break;
        case 2: ui->lineEdit_Ready_SPN2->setText(qstr);break;
        case 3: ui->lineEdit_Ready_SPN3->setText(qstr);break;
        case 4: ui->lineEdit_Ready_SPN4->setText(qstr);break;
        case 5: ui->lineEdit_Ready_SPN5->setText(qstr);break;
        case 6: ui->lineEdit_Ready_SPN6->setText(qstr);break;
        case 7: ui->lineEdit_Ready_SPN7->setText(qstr);break;
        case 8: ui->lineEdit_Ready_SPN8->setText(qstr);break;
        case 9: ui->lineEdit_Ready_SPN9->setText(qstr);break;
        default:break;
    }
}

void Widget::Slots_setReadyTextEditSRT(int name, int num){

    string str1 = std::to_string(name);
    if(name==-1)
        str1="";

    QString qstr = QString::fromStdString(str1);
    switch (num) {
        case 1: ui->lineEdit_Ready_SRT1->setText(qstr);break;
        case 2: ui->lineEdit_Ready_SRT2->setText(qstr);break;
        case 3: ui->lineEdit_Ready_SRT3->setText(qstr);break;
        case 4: ui->lineEdit_Ready_SRT4->setText(qstr);break;
        case 5: ui->lineEdit_Ready_SRT5->setText(qstr);break;
        case 6: ui->lineEdit_Ready_SRT6->setText(qstr);break;
        case 7: ui->lineEdit_Ready_SRT7->setText(qstr);break;
        case 8: ui->lineEdit_Ready_SRT8->setText(qstr);break;
        case 9: ui->lineEdit_Ready_SRT9->setText(qstr);break;
        default:break;
    }
}

void Widget::Slots_setTextEditAvgTime(double time, int num){
    string str1 = std::to_string(time);
    if(time==0)
        str1="";
    str1+=" s";
    QString qstr = QString::fromStdString(str1);
    switch (num) {
        case RR: ui->lineEdit_AvgTime_RR->setText(qstr);break;
        case DP: ui->lineEdit_AvgTime_DP->setText(qstr);break;
        case SPN: ui->lineEdit_AvgTime_SPN->setText(qstr);break;
        case SRT: ui->lineEdit_AvgTime_SRT->setText(qstr);break;
        default:break;
    }
}

void Widget::Slots_setRunTextEditPri(int pri,int num){
        string str1 = std::to_string(pri);
        if(pri==-1)
            str1="";
        QString qstr = QString::fromStdString(str1);
        switch (num) {
            case RR:   ui->lineEdit_Run_Pri_RR->setText(qstr);
                        break;
            case DP:   ui->lineEdit_Run_Pri_DP->setText(qstr);
                        break;
            case SPN:   ui->lineEdit_Run_Pri_SPN->setText(qstr);
                        break;
            case SRT:   ui->lineEdit_Run_Pri_SRT->setText(qstr);
                        break;
            default:break;
        }

}

void Widget::Slots_setRunTextEditTime(int time,int num){
        string str1 = std::to_string(time);
        if(time==0)
            str1="";
        QString qstr = QString::fromStdString(str1);
        switch (num) {
            case RR:   ui->lineEdit_Run_Time_RR->setText(qstr);
                        break;
            case DP:   ui->lineEdit_Run_Time_DP->setText(qstr);
                        break;
            case SPN:   ui->lineEdit_Run_Time_SPN->setText(qstr);
                        break;
            case SRT:   ui->lineEdit_Run_Time_SRT->setText(qstr);
                        break;
            default:break;
        }

}


void Widget::Slots_setReadyTextEditPriRR(int pri,int num){

    string str1 = std::to_string(pri);
    if(pri==-1)
        str1="";

    QString qstr = QString::fromStdString(str1);
//    ui->lineEdit_Run->setText(qstr);
    switch (num) {
        case 1: ui->lineEdit_Ready_Pri_RR1->setText(qstr);break;
        case 2: ui->lineEdit_Ready_Pri_RR2->setText(qstr);break;
        case 3: ui->lineEdit_Ready_Pri_RR3->setText(qstr);break;
        case 4: ui->lineEdit_Ready_Pri_RR4->setText(qstr);break;
        case 5: ui->lineEdit_Ready_Pri_RR5->setText(qstr);break;
        case 6: ui->lineEdit_Ready_Pri_RR6->setText(qstr);break;
        case 7: ui->lineEdit_Ready_Pri_RR7->setText(qstr);break;
        case 8: ui->lineEdit_Ready_Pri_RR8->setText(qstr);break;
        case 9: ui->lineEdit_Ready_Pri_RR9->setText(qstr);break;
        default:break;
    }
}


void Widget::Slots_setReadyTextEditPriDP(int pri,int num){

    string str1 = std::to_string(pri);
    if(pri==-1)
        str1="";

    QString qstr = QString::fromStdString(str1);
//    ui->lineEdit_Run->setText(qstr);
    switch (num) {
        case 1: ui->lineEdit_Ready_Pri_DP1->setText(qstr);break;
        case 2: ui->lineEdit_Ready_Pri_DP2->setText(qstr);break;
        case 3: ui->lineEdit_Ready_Pri_DP3->setText(qstr);break;
        case 4: ui->lineEdit_Ready_Pri_DP4->setText(qstr);break;
        case 5: ui->lineEdit_Ready_Pri_DP5->setText(qstr);break;
        case 6: ui->lineEdit_Ready_Pri_DP6->setText(qstr);break;
        case 7: ui->lineEdit_Ready_Pri_DP7->setText(qstr);break;
        case 8: ui->lineEdit_Ready_Pri_DP8->setText(qstr);break;
        case 9: ui->lineEdit_Ready_Pri_DP9->setText(qstr);break;
        default:break;
    }
}

void Widget::Slots_setReadyTextEditPriSPN(int pri, int num){

    string str1 = std::to_string(pri);
    if(pri==-1)
        str1="";
    QString qstr = QString::fromStdString(str1);
    switch (num) {
        case 1: ui->lineEdit_Ready_Pri_SPN1->setText(qstr);break;
        case 2: ui->lineEdit_Ready_Pri_SPN2->setText(qstr);break;
        case 3: ui->lineEdit_Ready_Pri_SPN3->setText(qstr);break;
        case 4: ui->lineEdit_Ready_Pri_SPN4->setText(qstr);break;
        case 5: ui->lineEdit_Ready_Pri_SPN5->setText(qstr);break;
        case 6: ui->lineEdit_Ready_Pri_SPN6->setText(qstr);break;
        case 7: ui->lineEdit_Ready_Pri_SPN7->setText(qstr);break;
        case 8: ui->lineEdit_Ready_Pri_SPN8->setText(qstr);break;
        case 9: ui->lineEdit_Ready_Pri_SPN9->setText(qstr);break;
        default:break;
    }
}

void Widget::Slots_setReadyTextEditPriSRT(int pri, int num){

    string str1 = std::to_string(pri);
    if(pri==-1)
        str1="";

    QString qstr = QString::fromStdString(str1);
    switch (num) {
        case 1: ui->lineEdit_Ready_Pri_SRT1->setText(qstr);break;
        case 2: ui->lineEdit_Ready_Pri_SRT2->setText(qstr);break;
        case 3: ui->lineEdit_Ready_Pri_SRT3->setText(qstr);break;
        case 4: ui->lineEdit_Ready_Pri_SRT4->setText(qstr);break;
        case 5: ui->lineEdit_Ready_Pri_SRT5->setText(qstr);break;
        case 6: ui->lineEdit_Ready_Pri_SRT6->setText(qstr);break;
        case 7: ui->lineEdit_Ready_Pri_SRT7->setText(qstr);break;
        case 8: ui->lineEdit_Ready_Pri_SRT8->setText(qstr);break;
        case 9: ui->lineEdit_Ready_Pri_SRT9->setText(qstr);break;
        default:break;
    }
}


void Widget::Slots_setReadyTextEditTimeRR(int time,int num){

    string str1 = std::to_string(time);
    if(time==0)
        str1="";

    QString qstr = QString::fromStdString(str1);
//    ui->lineEdit_Run->setText(qstr);
    switch (num) {
        case 1: ui->lineEdit_Ready_Time_RR1->setText(qstr);break;
        case 2: ui->lineEdit_Ready_Time_RR2->setText(qstr);break;
        case 3: ui->lineEdit_Ready_Time_RR3->setText(qstr);break;
        case 4: ui->lineEdit_Ready_Time_RR4->setText(qstr);break;
        case 5: ui->lineEdit_Ready_Time_RR5->setText(qstr);break;
        case 6: ui->lineEdit_Ready_Time_RR6->setText(qstr);break;
        case 7: ui->lineEdit_Ready_Time_RR7->setText(qstr);break;
        case 8: ui->lineEdit_Ready_Time_RR8->setText(qstr);break;
        case 9: ui->lineEdit_Ready_Time_RR9->setText(qstr);break;
        default:break;
    }
}


void Widget::Slots_setReadyTextEditTimeDP(int time,int num){

    string str1 = std::to_string(time);
    if(time==0)
        str1="";

    QString qstr = QString::fromStdString(str1);
//    ui->lineEdit_Run->setText(qstr);
    switch (num) {
        case 1: ui->lineEdit_Ready_Time_DP1->setText(qstr);break;
        case 2: ui->lineEdit_Ready_Time_DP2->setText(qstr);break;
        case 3: ui->lineEdit_Ready_Time_DP3->setText(qstr);break;
        case 4: ui->lineEdit_Ready_Time_DP4->setText(qstr);break;
        case 5: ui->lineEdit_Ready_Time_DP5->setText(qstr);break;
        case 6: ui->lineEdit_Ready_Time_DP6->setText(qstr);break;
        case 7: ui->lineEdit_Ready_Time_DP7->setText(qstr);break;
        case 8: ui->lineEdit_Ready_Time_DP8->setText(qstr);break;
        case 9: ui->lineEdit_Ready_Time_DP9->setText(qstr);break;
        default:break;
    }
}

void Widget::Slots_setReadyTextEditTimeSPN(int time, int num){

    string str1 = std::to_string(time);
    if(time==0)
        str1="";
    QString qstr = QString::fromStdString(str1);
    switch (num) {
        case 1: ui->lineEdit_Ready_Time_SPN1->setText(qstr);break;
        case 2: ui->lineEdit_Ready_Time_SPN2->setText(qstr);break;
        case 3: ui->lineEdit_Ready_Time_SPN3->setText(qstr);break;
        case 4: ui->lineEdit_Ready_Time_SPN4->setText(qstr);break;
        case 5: ui->lineEdit_Ready_Time_SPN5->setText(qstr);break;
        case 6: ui->lineEdit_Ready_Time_SPN6->setText(qstr);break;
        case 7: ui->lineEdit_Ready_Time_SPN7->setText(qstr);break;
        case 8: ui->lineEdit_Ready_Time_SPN8->setText(qstr);break;
        case 9: ui->lineEdit_Ready_Time_SPN9->setText(qstr);break;
        default:break;
    }
}

void Widget::Slots_setReadyTextEditTimeSRT(int time, int num){

    string str1 = std::to_string(time);
    if(time==0)
        str1="";

    QString qstr = QString::fromStdString(str1);
    switch (num) {
        case 1: ui->lineEdit_Ready_Time_SRT1->setText(qstr);break;
        case 2: ui->lineEdit_Ready_Time_SRT2->setText(qstr);break;
        case 3: ui->lineEdit_Ready_Time_SRT3->setText(qstr);break;
        case 4: ui->lineEdit_Ready_Time_SRT4->setText(qstr);break;
        case 5: ui->lineEdit_Ready_Time_SRT5->setText(qstr);break;
        case 6: ui->lineEdit_Ready_Time_SRT6->setText(qstr);break;
        case 7: ui->lineEdit_Ready_Time_SRT7->setText(qstr);break;
        case 8: ui->lineEdit_Ready_Time_SRT8->setText(qstr);break;
        case 9: ui->lineEdit_Ready_Time_SRT9->setText(qstr);break;
        default:break;
    }
}


