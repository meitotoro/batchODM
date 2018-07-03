#include "task.h"
#include "sendfiles.h"

Task::Task(QNetworkAccessManager* netman,QStringList& list, QString& batchName,QObject *parent) : QObject(parent),
    _netman(netman),_list(list),_batchName(batchName)
{
}
void Task::sendFiles(){
   SendFiles files=new SendFiles(_netman,_list,_batchName);
   files.send();
}

void Task::run() {
    // 1. 执行docker
    // 2. 定时更新状态 timer
    // 3. 完成时停止更新状态 connect
}
