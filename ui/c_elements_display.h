#ifndef C_ELEMENTS_DISPLAY_H
#define C_ELEMENTS_DISPLAY_H

#include <QWidget>
#include <QPixmap>
#include <QGraphicsDropShadowEffect>
#include <QMap>
#include <QList>
#include <QDebug>
#include "ui.h"
#include "c_element_dialog.h"

namespace Ui {
class c_elements_display;
}

class c_elements_display : public QWidget
{
    Q_OBJECT

public:
    explicit c_elements_display(QWidget *parent = nullptr);
    ~c_elements_display() override;
    static QMap<QString,QString> set_frTo_En_elem();
    static QMap<QString,int> set_frToId_elem();

private:
    Ui::c_elements_display *ui;
    static QMap<QString,QString> frToEn_elem;
    static QMap<QString,int> frToId_elem;
    QList<QString> elems;
    QList<bool> elems_chosen;

    void update_view();

public slots:
    void setElements(QList<QString> new_elems);
    void mouseDoubleClickEvent(QMouseEvent *event) override;

signals:
    void newElements(QList<QString> new_elem);

};

#endif // C_ELEMENTS_DISPLAY_H
