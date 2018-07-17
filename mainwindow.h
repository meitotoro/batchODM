#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QVBoxLayout>
#include <QCloseEvent>
#include <QMenu>
#include <QString>
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
    void slotLocalTestViewContextMenu(const QPoint &position);

private slots:

    void on_cb_AllSelected_stateChanged();

    void on_ok_button_clicked();

    void on_pushButton_3_clicked();



    void addFolderDialog();

private:
    Ui::MainWindow *ui;
    taskDialog dialog;
    QList<ImageListItem*> imageList;
    QNetworkAccessManager* netman;
    QVBoxLayout *vLayout;
    void httpConnectTest();
    void creatActions();
    void setDeleteActionStatus(QAction* deleteAction);
    void setPauseActionStatus(QAction* pauseAction);
    void setStartActionStatus(QAction* startAction);
    QAction* creatAction(QString objectName,QString text,QString pixmap_fileName,QString pixmap_hover_fileName);
    QList<QAction *> actions;
    QMenu *rightMenu;

protected:
     void closeEvent(QCloseEvent *event);

};

#endif // MAINWINDOW_H
