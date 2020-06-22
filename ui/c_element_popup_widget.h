#ifndef C_ELEMENT_POPUP_WIDGET_H
#define C_ELEMENT_POPUP_WIDGET_H

#include <QWidget>
#include <QCheckBox>
#include <QPushButton>
#include <QList>
#include <QMap>
#include <QDebug>
#include "ui/ui.h"

namespace Ui {
class c_element_popup_widget;
}

class c_element_popup_widget : public QWidget
{
    Q_OBJECT

public:
    explicit c_element_popup_widget(QWidget *parent = nullptr);
    ~c_element_popup_widget();

    void setElems(QList<bool> elems);
    QList<bool> getElems();

public slots:
    void slot_accepted();
    void slot_add_element();
    void updateView();

private:
    Ui::c_element_popup_widget *ui;
    int number_checked;
    QList<QCheckBox*> checklist;
    QList<QString> list_element;
    QList<QString> chosen_elements;
    QMap<QString,QString> frToEn_elem;
};

#endif // C_ELEMENT_POPUP_WIDGET_H
