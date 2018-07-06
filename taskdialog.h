#ifndef TASKDIALOG_H
#define TASKDIALOG_H

#include <QDialog>
#include <QString>
#include <QStringList>

class QNetworkAccessManager;

namespace Ui {
class taskDialog;
}

class taskDialog : public QDialog
{
    Q_OBJECT

public:
    explicit taskDialog(QWidget *parent = 0);
    ~taskDialog();
    QString folder;
    QString folderName;
    QStringList fileList;

private slots:
    void on_ok_button_clicked();

    void on_pushButton_clicked();

    void on_cancel_clicked();

private:
    Ui::taskDialog *ui;

};

#endif // TASKDIALOG_H
