#include "mainwindow.h"
#include <QApplication>
#include "taskmanager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    TaskManager taskManager=new TaskManager();

    return a.exec();
}
