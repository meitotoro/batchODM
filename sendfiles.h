#ifndef SENDFILES_H
#define SENDFILES_H

#include <deque>
#include <QObject>
#include <QString>

class QNetworkAccessManager;
class QStringList;

class SendFiles : public QObject
{
    Q_OBJECT
public:
    SendFiles(QNetworkAccessManager* netman,QStringList& list, QString& batchName);
    void send(QNetworkAccessManager* netman);

private:
    void sendAll(QNetworkAccessManager* netman);
    void sendFile(QNetworkAccessManager* netman, QString& name);
    void waitForAllFinished();

signals:
    void allFinished();

private:
    QString _batchName;
    std::deque<QString> _filesToSend; // 待发送的文件队列
    size_t _filesOnAir = 0; // 尚未传输完成的文件数量
};

#endif // SENDFILES_H
