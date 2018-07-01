#ifndef IMAGELISTITEM_H
#define IMAGELISTITEM_H

#include <QWidget>

namespace Ui {
class ImageListItem;
}

class ImageListItem : public QWidget
{
    Q_OBJECT

public:
    explicit ImageListItem(QString folder,QString folderName,QWidget *parent = 0);
    ~ImageListItem();

private:
    Ui::ImageListItem *ui;

};

#endif // IMAGELISTITEM_H
