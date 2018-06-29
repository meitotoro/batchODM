/********************************************************************************
** Form generated from reading UI file 'taskdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TASKDIALOG_H
#define UI_TASKDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_taskDialog
{
public:
    QPushButton *ok_button;
    QCheckBox *checkBox;
    QWidget *widget;
    QLabel *label;
    QLineEdit *folderName;
    QPushButton *pushButton_3;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *folder;
    QPushButton *pushButton;
    QListWidget *imageList;

    void setupUi(QDialog *taskDialog)
    {
        if (taskDialog->objectName().isEmpty())
            taskDialog->setObjectName(QStringLiteral("taskDialog"));
        taskDialog->resize(651, 512);
        ok_button = new QPushButton(taskDialog);
        ok_button->setObjectName(QStringLiteral("ok_button"));
        ok_button->setGeometry(QRect(170, 460, 111, 31));
        QFont font;
        font.setPointSize(10);
        ok_button->setFont(font);
        checkBox = new QCheckBox(taskDialog);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setGeometry(QRect(20, 430, 91, 19));
        checkBox->setFont(font);
        checkBox->setChecked(true);
        widget = new QWidget(taskDialog);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(20, 10, 501, 61));
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(11, 11, 85, 17));
        label->setFont(font);
        folderName = new QLineEdit(widget);
        folderName->setObjectName(QStringLiteral("folderName"));
        folderName->setGeometry(QRect(103, 15, 271, 21));
        folderName->setMaximumSize(QSize(16777215, 30));
        pushButton_3 = new QPushButton(taskDialog);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(340, 460, 101, 31));
        pushButton_3->setFont(font);
        widget_2 = new QWidget(taskDialog);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        widget_2->setGeometry(QRect(20, 80, 611, 51));
        horizontalLayout_2 = new QHBoxLayout(widget_2);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(widget_2);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font);
        label_2->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(label_2);

        folder = new QLineEdit(widget_2);
        folder->setObjectName(QStringLiteral("folder"));
        folder->setMaximumSize(QSize(16777215, 30));
        folder->setSizeIncrement(QSize(0, 0));

        horizontalLayout_2->addWidget(folder);

        pushButton = new QPushButton(widget_2);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setFont(font);

        horizontalLayout_2->addWidget(pushButton);

        imageList = new QListWidget(taskDialog);
        imageList->setObjectName(QStringLiteral("imageList"));
        imageList->setGeometry(QRect(20, 140, 611, 281));

        retranslateUi(taskDialog);

        QMetaObject::connectSlotsByName(taskDialog);
    } // setupUi

    void retranslateUi(QDialog *taskDialog)
    {
        taskDialog->setWindowTitle(QApplication::translate("taskDialog", "Dialog", nullptr));
        ok_button->setText(QApplication::translate("taskDialog", "\347\241\256\345\256\232", nullptr));
        checkBox->setText(QApplication::translate("taskDialog", "\346\255\243\345\260\204\345\275\261\345\203\217", nullptr));
        label->setText(QApplication::translate("taskDialog", "\344\273\273\345\212\241\345\220\215\347\247\260\357\274\232", nullptr));
        pushButton_3->setText(QApplication::translate("taskDialog", "\345\217\226\346\266\210", nullptr));
        label_2->setText(QApplication::translate("taskDialog", "\346\226\207\344\273\266\345\244\271\350\267\257\345\276\204\357\274\232", nullptr));
        folder->setText(QString());
        pushButton->setText(QApplication::translate("taskDialog", "\351\200\211\346\213\251", nullptr));
    } // retranslateUi

};

namespace Ui {
    class taskDialog: public Ui_taskDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TASKDIALOG_H
