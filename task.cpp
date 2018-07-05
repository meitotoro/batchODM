#include "task.h"
#include "sendfiles.h"
#include "docker.h"
#include <QTimer>

Task::Task(QNetworkAccessManager* netman,QStringList& list, QString& batchName) :
    _netman(netman),_list(list),_batchName(batchName)
{
    timer=new QTimer();
    docker=new Docker(_batchName);
}
void Task::sendFiles(){
    SendFiles *files=new SendFiles(_netman,_list,_batchName);
    files->send(_netman);
}

void Task::run() {
    // 1. 执行docker
    docker->run(_netman);
    // 2. 定时更新状态 timer
    connect(timer,&QTimer::timeout,[=](){
        docker->get_progress(_netman,0,110);
        int progress=docker->get_curProgress();
    });
    connect(docker,&Docker::dockerRun,[=](){
        timer->start(2000);
    });
    //3.文件太少是弹出提示,断开连接
    connect(docker,&Docker::littleImage,[=](){
        timer->disconnect();
    });
    // 4. 完成时停止更新状态 connect
    connect(docker,&Docker::resultReady,[=](){
        emit dockerFinished();
        timer->stop();
        timer->disconnect();

    });

}
void Task::stop(){
    docker->stop(_netman);

}
