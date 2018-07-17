#include "taskmanager.h"
#include <QTimer>
#include <QEventLoop>
#include "task.h"
#include <QDebug>
#include <QMutex>

TaskManager::TaskManager()

{

}
void TaskManager::addTask(Task* task){
    taskList.push_back(task);
    selected.push_back(false);
}

void TaskManager::select(int index){
    selected[index] = true;
}
void TaskManager::deselect(int index){
    selected[index] = false;
}
void TaskManager::setParalNum(int num){
    _num=num;
}
bool TaskManager::getDockerStatus(int index){
    Task* t=taskList[index];
    if(t->dockerRun){
        return true;
    }else{
        return false;
    }
}
void TaskManager::runSelected() {
    std::deque<Task*> tasksToSend;
    for (int i = 0; i < selected.size(); ++i) {
        if (selected[i]) {
            tasksToSend.push_back(taskList[i]);
            tasksToSend[i]->aborted=false;
        }
    }
    int _sent=0;
    int i=-1;
    auto mutex=std::make_shared<QMutex>();
    while (!tasksToSend.empty()) {
        QEventLoop loop;
        // TODO: 等待一个任务结束（将任务结束信号连接到循环的退出函数）
        if (_sent < _num) {
            Task *t=tasksToSend.front();
            connect(t,&Task::dockerFinished, &loop,[&](){
                mutex->lock();
                _sent=_sent-1;
                &QEventLoop::quit;
                mutex->unlock();
            });
            i++;
            tasksToSend.pop_front();
            t->sendFiles();
            emit filesSended(i);
            connect(t,&Task::progressUpdated,[=](int progress){
                emit getPorgress(i,progress);
            });
            connect(t,&Task::dockerFinished,[=](){
                t->get_resultFiles();
            });
            connect(t,&Task::fileReturned,[=](){
                emit fileReturned(i);
            });
            connect(t,&Task::littleImage,[=](){
                emit littleImage(i);

            });
            t->run();
            ++_sent;
        }else{
            loop.exec();
        }
    }
}


void TaskManager::stopSelected() {
    for(int i=0;i<taskList.size();i++){
        if(selected[i]){
            Task *task=taskList[i];
            task->stop();
        }
    }
}

void TaskManager::pauseSelected(int i){
    if(selected[i]){
        Task *task=taskList[i];
        task->pause();
    }

}
void TaskManager::restartSelected(int i){
    if(selected[i]){
        Task *task=taskList[i];
        task->restart();
    }

}

