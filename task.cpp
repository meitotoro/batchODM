#include "task.h"
#include "sendfiles.h"
#include "docker.h"
#include <QTimer>
#include <QNetworkAccessManager>
#include <QMessageBox>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QDir>
#include <QFile>
#include <QUrlQuery>



Task::Task(QStringList& list, QString folder, QString& batchName) :
    _list(list),_folder(folder),_batchName(batchName),dockerRun(false),aborted(false),files(nullptr)
{
    timer=new QTimer();
    docker=new Docker(_batchName);
}
void Task::sendFiles(){
    files=new SendFiles(_netman,_list,_batchName);
    files->send(_netman);
}

void Task::run() {

    if(aborted){
        aborted=false;
        return;
    }
    // 执行docker
    docker->run(_netman);    
    // 1. 定时更新状态 timer
    curProgress=0;
    connect(timer,&QTimer::timeout,[=](){
        docker->get_progress(_netman,0,110);
        preProgress=curProgress;
        //qDebug()<<_batchName+" preProgress: "+QString::number(preProgress);
        curProgress=docker->get_curProgress();
        //qDebug()<<_batchName+" curProgress: "+QString::number(curProgress);
        if(curProgress>preProgress){
            emit progressUpdated(curProgress);
        }
    });
    connect(docker,&Docker::dockerRun,[=](){
        timer->start(2000);
        dockerRun=true;
    });
    //2.文件太少是弹出提示,断开连接
    connect(docker,&Docker::littleImage,[=](){
        timer->disconnect();
        dockerRun=false;
        emit littleImage();
    });
    // 3. 完成时停止更新状态 connect
    connect(docker,&Docker::resultReady,[=](){
        emit dockerFinished();
        emit progressUpdated(110);
        timer->stop();
        timer->disconnect();
    });
    //4.收到dockerStop命令，停止更新progress状态
    connect(docker,&Docker::dockerStop,[=](){
        timer->stop();
        timer->disconnect();
    });
}

void Task::stop(){
    if(dockerRun){
        docker->stop(_netman);
        connect(docker,&Docker::dockerStop,[=](){
            dockerRun=false;
        });
    }else{
        aborted=true;
        if(files){
            files->stop(_netman);
        }
    }
}

void Task::pause(){
    if(dockerRun){
        docker->pause(_netman);
        connect(docker,&Docker::dockerPause,[=](){
            dockerRun=false;
        });
    }else{
        aborted=true;
        if(files){
            files->stop(_netman);
        }
    }
}
void Task::restart(){
    if(!dockerRun){
        docker->restart(_netman);
        connect(docker,&Docker::dockerRestart,[=](){
            dockerRun=true;
        });
    }
}
void Task::get_resultFiles(){
        QString path =_folder+"/results.zip";
        QDir dir(_folder);
        if(!dir.exists(path))
        {
            dir.mkpath(_folder);
            qDebug()<<"directory now exists";
        }
        auto file = std::make_shared<QFile>(path);
        //QFile *file1=new QFile(path);
        file->open(QIODevice::ReadWrite);
        QUrlQuery params;
        params.addQueryItem("folder", _batchName);
        QUrl url("http://192.168.188.10:9000/orthomap?"+params.query());
        QNetworkRequest request(url);
        auto reply=_netman->get(request);
        connect(reply, &QNetworkReply::readyRead,
                [=](){
            std::vector<char> buffer(4096);
            qint64 bytesRead;
            while ((bytesRead=reply->read(&buffer[0],buffer.size()))>0){
                file->write(&buffer[0],bytesRead);
            }
        });
        connect(reply, &QNetworkReply::finished,
                [=](){
            file->close();
            reply->deleteLater();
            emit fileReturned();
        });
}

void Task::setNetworkManager(QNetworkAccessManager* netman){
    _netman=netman;
}


QNetworkAccessManager *Task::_netman=nullptr;
