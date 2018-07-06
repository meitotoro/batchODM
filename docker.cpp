#include "Docker.h"
#include <QUrlQuery>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QMessageBox>
#include <QDialog>
#include <QTimer>

Docker::Docker(QString &batchName):
    _batchName(batchName)
{

}
void Docker::run(QNetworkAccessManager *netman)
{
    QUrlQuery params;
    params.addQueryItem("folder", _batchName);
    QUrl url("http://192.168.188.10:9000/docker?"+params.query());
    QNetworkRequest request(url);
    auto reply=netman->get(request);
    connect(reply, &QNetworkReply::finished,
            [=](){
        reply->deleteLater();
        //QMessageBox::information(_parent,"提示","start run docker",QMessageBox::Ok);
        emit dockerRun();
    });
}
void Docker::stop(QNetworkAccessManager *netman)
{
    QUrlQuery params;
    params.addQueryItem("folder", _batchName);
    QUrl url("http://192.168.188.10:9000/stopdocker?"+params.query());
    QNetworkRequest request(url);
    auto reply=netman->get(request);
    connect(reply, &QNetworkReply::finished,[=](){
        QByteArray ba=reply->readAll();
        QString s_data = QString::fromUtf8(ba.data());
        //QMessageBox::information(this,"提示",s_data,QMessageBox::Ok);
        reply->deleteLater();

    });
   // emit dockerStopped();
}
//获取当前的log进度，修改_curProgress值
void Docker::get_progress(QNetworkAccessManager *netman,int min_progress,int max_progress)
{
    QUrlQuery params;
    params.addQueryItem("folder", _batchName);
    QUrl url("http://192.168.188.10:9000/progress?"+params.query());
    QNetworkRequest request(url);
    auto reply=netman->get(request);
    connect(reply, &QNetworkReply::finished,[=](){
        QByteArray ba=reply->readAll();
        QString s_data = QString::fromUtf8(ba.data());
        s_data=s_data.replace("\u001B[94m","");
        s_data=s_data.replace("\u001B[92m","");
        s_data=s_data.replace("\u001B[0m","");
        s_data=s_data.replace("\u001B[0;m","");
        QStringList list_data=s_data.split(QRegExp("\n|\r\n|\r"),QString::SkipEmptyParts);
        if(list_data.indexOf("[WARNING] Initial residual too low: 0 < 0.000001")>=0){
            QMessageBox::information(_parent,"提示","图片量太少，请重新选择图片",QMessageBox::Ok);
            reply->abort();
            emit littleImage();
            _curProgress=0;
        }else {
            if(s_data!=""){
                qDebug()<<s_data;
                QString temp = QString::fromUtf8("running PYTHONPATH");
                if(s_data.contains(temp)){
                    int step=(max_progress-min_progress)/11;
                    qDebug()<<step;
                    _curProgress+=step;
                }
                if (list_data.indexOf("OpenDroneMap app finished")>=0){
                    qDebug()<<"OpenDroneMap app finished";
                    _curProgress=max_progress;
                    //QMessageBox::information(_parent,"提示","finished",QMessageBox::Ok);
                    emit resultReady();
                }
            }
        }
        reply->deleteLater();
    });
    connect(reply,static_cast<void (QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error),[](QNetworkReply::NetworkError code){
        qDebug()<<"error:"<<code;

    });
//    connect(this,Docker::dockerStopped,[=](){
//        reply->abort();
//    });


}

//返回当前的进度值
int Docker::get_curProgress(){
    qDebug()<<_curProgress;
    return _curProgress;
}

Docker::~Docker(){

}
