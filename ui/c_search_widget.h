#ifndef C_SEARCH_WIDGET_H
#define C_SEARCH_WIDGET_H

#include <algorithm>
#include <QWidget>
#include <QQuickItem>
#include <QtMath>
#include <QGraphicsDropShadowEffect>
#include <QLineEdit>
#include <QAbstractItemView>
#include <QStandardItemModel>
#include "ui.h"
#include "utilities/c_dbmanager.h"
#include "utilities/utilities.h"

namespace Ui {
class c_search_widget;
}

class c_search_widget : public QWidget
{
    Q_OBJECT

public:
    explicit c_search_widget(c_dbmanager* manager,QWidget *parent = nullptr);
    ~c_search_widget();

private:
    Ui::c_search_widget *ui;
    bool final;
    bool block;
    QQuickItem *slider;
    int lvl;
    QStringList paliers;
    c_dbmanager *dbmanager;


public slots:
    void slot_slider_first_moved(qreal val);
    void slot_slider_second_moved(qreal val);
    void slot_lvl_low_changed(int val);
    void slot_lvl_high_changed(int val);
    void slot_niveau_preDef_changed(const QString& string);
    void slot_rarity_change_state(bool checked);
    void slot_search();
    void init_comboBox(QComboBox* cb);
    void slot_reset();
   static bool compare_pair_id_lvl(QPair<int,int> p1, QPair<int,int> p2);
    void setLvl(int lvl);

signals:
    void new_search_result(QList<int>);
};

#endif // C_SEARCH_WIDGET_H
