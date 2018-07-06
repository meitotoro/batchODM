#include "task.h"
#include "sendfiles.h"
#include "docker.h"
#include <QTimer>
#include <QNetworkAccessManager>


Task::Task(QStringList& list, QString& batchName) :
    _list(list),_batchName(batchName)
{
    timer=new QTimer();
    docker=new Docker(_batchName);
}
void Task::sendFiles(){
    SendFiles *files=new SendFiles(_netman,_list,_batchName);
    files->send(_netman);
}

void Task::run() {
    // 执行docker
    docker->run(_netman);
    // 1. 定时更新状态 timer
    curProgress=0;
    connect(timer,&QTimer::timeout,[=](){
        docker->get_progress(_netman,0,110);
        preProgress=curProgress;
        qDebug()<<_batchName+" preProgress: "+QString::number(preProgress);
        curProgress=docker->get_curProgress();
        qDebug()<<_batchName+" curProgress: "+QString::number(curProgress);
        if(curProgress>preProgress){
            emit progressUpdated(curProgress);
        }
    });
    connect(docker,&Docker::dockerRun,[=](){
        timer->start(2000);
    });
    //2.文件太少是弹出提示,断开连接
    connect(docker,&Docker::littleImage,[=](){
        timer->disconnect();
    });
    // 3. 完成时停止更新状态 connect
    connect(docker,&Docker::resultReady,[=](){
        emit dockerFinished();
        timer->stop();
        timer->disconnect();

    });
}

void Task::stop(){
    docker->stop(_netman);

}

void Task::setNetworkManager(QNetworkAccessManager* netman){
    _netman=netman;
}


QNetworkAccessManager *Task::_netman=nullptr;
