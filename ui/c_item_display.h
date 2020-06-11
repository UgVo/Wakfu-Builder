#ifndef C_ITEM_DISPLAY_H
#define C_ITEM_DISPLAY_H

#include <QWidget>
#include <QPixmap>
#include <QDebug>
#include <QColor>
#include <QList>
#include <QLabel>
#include <QVBoxLayout>
#include <QRegularExpression>
#include "utilities/c_item.h"
#include "utilities/c_dbmanager.h"
#include "ui.h"

namespace Ui {
class c_item_display;
}

class c_item_display : public QWidget
{
    Q_OBJECT

    static const int heigth_label = 18;
    static const int indent_effect = 12;
    static const int indent_title = 5;
    static const QString color_background;
    static const QString color_foreground;

public:
    explicit c_item_display(c_item item, QWidget *parent = nullptr);
    ~c_item_display();
    QString replace_image(QString text);
    void completeData(c_dbmanager *manager);
    void updateView();
    c_item getItem();

    const static QList<QString> color_rarity;

private:
    Ui::c_item_display *ui;
    c_item _item;
    int size_layout;
    QList<QLabel*> label_header_list;
    QList<QLabel*> label_use_list;
    QList<QLabel*> label_equip_list;
    bool data_complete;
    QString imageDir;
};


#endif // C_ITEM_DISPLAY_H
