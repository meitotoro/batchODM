﻿#include "taskmanager.h"
#include <QTimer>
#include <QEventLoop>
#include "task.h"
TaskManager::TaskManager(QNetworkAccessManager *netman):_netman(netman)

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
void TaskManager::runSelected() {
    std::deque<Task*> tasksToSend;
    for (int i = 0; i < selected.size(); ++i) {
        if (selected[i]) {
            tasksToSend.push_back(taskList[i]);
        }
    }
    int _sent=0;
    while (!tasksToSend.empty()) {
        QEventLoop loop;
        // TODO: 等待一个任务结束（将任务结束信号连接到循环的退出函数）
        if (_sent < _num) {
            Task *t=tasksToSend.front();
            connect(t,&Task::dockerFinished, &loop,[&](){
                _sent=_sent-1;
                &QEventLoop::quit;
            });
            tasksToSend.pop_front();
            t->sendFiles();
            t->run();
            ++_sent;
        }
         loop.exec();
    }
}


void TaskManager::stopSelected() {
    for (int i = 0; i < selected.size(); ++i) {
        if (selected[i]) {
            taskList[i]->stop();
        }
    }
}
