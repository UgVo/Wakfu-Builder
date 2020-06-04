#ifndef C_ITEM_LITE_H
#define C_ITEM_LITE_H

#include <QWidget>
#include <QTimer>
#include "utilities/utilities.h"
#include "ui.h"
#include "c_item_display.h"
#include "utilities/c_dbmanager.h"

namespace Ui {
class c_item_lite;
}

class c_item_lite : public QWidget
{
    Q_OBJECT

public:
    explicit c_item_lite(c_dbmanager * database_manager = nullptr, c_item item = c_item(), QWidget *parent = nullptr);
    ~c_item_lite() override;
    void set_icon();
    bool event(QEvent *event) override;
    void setDatabase_manager(c_dbmanager* manager);

    c_item item() const;

private:
    Ui::c_item_lite *ui;
    c_item _item;
    c_item_display *it_display;
    QWidget* _parent;
    c_dbmanager *_database_manager;
    QTimer *timer;

public slots:
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void check_mouse_over();
    void setItem(const c_item &item);
    void updateView();

signals:
    void item_doubleCliked(c_item item);
};

#endif // C_ITEM_LITE_H
