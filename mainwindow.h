#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QVBoxLayout>
#include "taskdialog.h"
#include "imagelistitem.h"
#include "taskmanager.h"

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

class QNetworkAccessManager;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    TaskManager *taskManager;

signals:
    void httpConnectFailed();
    void httpConnectSuccess();

private slots:
    void reminder(int i);

private slots:
    void on_pushButton_clicked();

    void on_cb_AllSelected_stateChanged();

    void on_ok_button_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    taskDialog dialog;
    QList<ImageListItem*> imageList;
    QNetworkAccessManager* netman;
    QVBoxLayout *vLayout;
    void httpConnectTest();

};

#endif // MAINWINDOW_H
