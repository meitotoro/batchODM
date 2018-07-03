#include "task.h"
#include "sendfiles.h"

Task::Task(QObject *parent,QNetworkAccessManager* netman,QStringList& list, QString& batchName) : QObject(parent)
{
  _netman=netman;
  _list=list;
  _batchName=batchName;
}
Task:sendFiles(){
   SendFiles files=new SendFiles(_netman,_list,_batchName);


}
