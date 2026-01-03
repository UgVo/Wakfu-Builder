#ifndef C_ITEM_DISPLAY_H
#define C_ITEM_DISPLAY_H

#include <QColor>
#include <QDebug>
#include <QLabel>
#include <QList>
#include <QPixmap>
#include <QRegularExpression>
#include <QVBoxLayout>
#include <QWidget>

#include "ui.h"
#include "utilities/c_dbmanager.h"
#include "utilities/c_item.h"

namespace Ui {
class c_item_display;
}

class c_item_display : public QWidget {
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
    void setItem(c_item item);

    const static QList<QString> color_rarity;

    void setCmp_equip(bool value);

   private:
    Ui::c_item_display *ui;
    c_item _item;
    int size_layout;
    QList<QLabel *> label_header_list;
    QList<QLabel *> label_use_list;
    QList<QLabel *> label_equip_list;
    bool data_complete;
    QString imageDir;
    bool cmp_equip;
};

#endif  // C_ITEM_DISPLAY_H
