#ifndef C_ITEM_VIEWER_H
#define C_ITEM_VIEWER_H

#include <QWidget>
#include <QStackedLayout>
#include <QLabel>
#include <QList>
#include <QStringList>
#include <QVBoxLayout>
#include <QString>
#include <QMenu>
#include <QAction>
#include <QTimer>
#include "utilities/c_item.h"
#include "c_element_dialog.h"
#include "c_elements_display.h"
#include "c_item_display.h"


namespace Ui {
class c_item_viewer;
}

class c_item_viewer : public QWidget
{
    Q_OBJECT

public:
    explicit c_item_viewer(const QString position = c_item::NONE, QWidget *parent = nullptr);
    ~c_item_viewer();
    void setItem(c_item *item =  nullptr);
    void updateView();

private:
    void setBackgroundImage();


    Ui::c_item_viewer *ui;
    QStackedLayout *image_layout;
    QLabel *background;
    QLabel *image;
    QList<QLabel*> elements;
    QMap<QString,QPixmap> images_elements;
    QVBoxLayout *elements_layout;
    bool own_item;
    QString position;

    c_item* item;
    bool disabled;

    c_item_display *it_display;
    QWidget* _parent;
    QTimer * timer;
    bool block;

public slots:
    void slot_context_menu(const QPoint &pos);
    void slot_unequip();
    void slot_refresh_elements();
    void disable(int gfxId);
    void enable();
    c_item *get_item();
    c_item get_item_const() const;
    QString getPosition() const;
    bool event(QEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void check_mouse_over();

signals:
    void unequip(QString position);
    void elementsChanged();
    void clicked(QString position);

};

#endif // C_ITEM_VIEWER_H
