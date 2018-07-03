#include "sendfiles.h"
#include <QApplication>
#include <QEventLoop>
#include <QFileInfo>
#include <QMessageBox>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QUrlQuery>

SendFiles::SendFiles(QNetworkAccessManager* netman,QStringList &list, QString &batchName) :
    _batchName(batchName)
{
    // 将所有文件加入待发送队列
    for (auto& filename : list) {
        _filesToSend.push_back(filename);
    }
    QUrlQuery params;
    params.addQueryItem("folder", _batchName);
    QUrl url("http://192.168.188.10:9000/delteImage?"+params.query());
    QNetworkRequest request(url);
    QNetworkReply* reply = netman->get(request);
    connect(reply, &QNetworkReply::finished, [=]() {
        QByteArray rep = reply->readAll();
        qDebug()<<QString::fromUtf8(rep);
        reply->deleteLater();
    });
}

void SendFiles::send(QNetworkAccessManager *netman) {
    // 算法说明：
    // 0. 初始情况：所有文件都在待发送队列中
    // 1. 如果队列非空，则将队列中的所有文件发送出去；如果已经为空则全部发送完成，结束
    // 2. 等待所有文件传输完成或异常终止，所有未完成的文件会重新加入队列
    // 3. 返回1.重新执行
    int i=0;
    while (!_filesToSend.empty()) {
        // 队列中还有待发送的文件，全部发送并等待连接完成
        // 没发送完的文件会重新进入队列（在回调函数中处理）
        i++;
        QString print = "第" + QString::number(i)+ "次循环";
        qDebug()<<print;
        sendAll(netman);
        waitForAllFinished();
    }
}

void SendFiles::sendAll(QNetworkAccessManager *netman)
{
    // 设置待传输文件的数量
    _filesOnAir = _filesToSend.size();
    for(auto& item : _filesToSend) { qDebug() << item; }
    // 发送所有文件
    while (!_filesToSend.empty()) {
        // 取队列中的第一个，将其移出队列并发送
        auto file_path = _filesToSend.front();
        _filesToSend.pop_front();
        sendFile(netman, file_path);
    }
}

void SendFiles::sendFile(QNetworkAccessManager* netman, QString &file_path)
{

    QFileInfo info = QFileInfo(file_path);
    QString file_name = info.fileName();
    // 初始化请求
    QUrlQuery params;
    params.addQueryItem("folder", _batchName);
    params.addQueryItem("name", file_name);
    QUrl url("http://192.168.188.10:9000/transformap?"+params.query());
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image/jpeg"));
    // 读文件内容
    QFile file(file_path);
    file.open(QIODevice::ReadOnly);
    QByteArray ba = file.readAll();
    file.close();
    // 将文件内容通过请求发送
    QNetworkReply* reply = netman->post(request, ba);
    connect(reply, &QNetworkReply::finished, [=]() {
        auto code = reply->error();
        if(code != QNetworkReply::NoError) {
            // 出现错误，将文件重新加入队列
            qDebug()<< "error: " << code;
            qDebug()<<reply->errorString();
            qDebug()<<reply->attribute( QNetworkRequest::HttpStatusCodeAttribute).toInt();
            reply->abort();
            _filesToSend.push_back(file_path);
        }
        QByteArray rep = reply->readAll();
        qDebug()<<QString::fromUtf8(rep);
        --_filesOnAir;
        if (_filesOnAir == 0) {
            qDebug() << "Sending file finished! ";
            emit allFinished();
        }
        reply->deleteLater();
    });
}

void SendFiles::waitForAllFinished()
{
    // 在收到 allFinished 信号前等待，保持在函数里不返回
    // 参考：https://rohieb.wordpress.com/2010/07/08/qt-nearly-synchronous-qnetworkaccessmanager-calls/
    QEventLoop loop;
    connect(this, &SendFiles::allFinished, &loop, &QEventLoop::quit);
    loop.exec();
}
