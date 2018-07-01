#include "imagelistitem.h"
#include "ui_imagelistitem.h"

ImageListItem::ImageListItem(QString folder, QString folderName, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImageListItem)
{
    ui->setupUi(this);
    ui->folder->setText(folder);
    ui->folderName->setText(folderName);

}

ImageListItem::~ImageListItem()
{
    delete ui;
}
