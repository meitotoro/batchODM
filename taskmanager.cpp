#include "taskmanager.h"
#include <QTimer>
#include <QEventLoop>
TaskManager::TaskManager()
{

}
void TaskManager::addTask(Task task){
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
    std::deque<Task> tasksToSend;
    for (int i = 0; i < selected.size(); ++i) {
        if (selected[i]) {
            tasksToSend.push_back(taskList[i]);
        }
    }

    while (!tasksToSend.empty()) {
        if (_sent < _num) {
            Task t = tasksToSend.front();
            tasksToSend.pop_front();
            t.sendFiles();
            t.run();
            ++_sent;
        } else {
            QEventLoop loop;
            // TODO: 等待一个任务结束（将任务结束信号连接到循环的退出函数）
            loop.exec();
        }
    }
}

void TaskManager::stopSelected() {
    for (int i = 0; i < selected.size(); ++i) {
        if (selected[i]) {
            taskList[i].stop();
        }
    }
}
