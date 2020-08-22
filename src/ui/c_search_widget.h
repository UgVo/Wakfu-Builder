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
#include <QComboBox>
#include <QCompleter>
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
    explicit c_search_widget(c_dbmanager* manager, QCompleter* search_completer, QWidget *parent = nullptr);
    ~c_search_widget();

private:
    Ui::c_search_widget *ui;
    bool final;
    bool block;
    QQuickItem *slider;
    int lvl;
    QStringList paliers;
    c_dbmanager *dbmanager;
    QList<QComboBox*> cb_carac_list;
    QList<QComboBox*> cb_carac_condi;
    QCompleter* completer;

    int numberShown;


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
    void slot_load_search_position(QString position);
    void slot_combi_search();

    void set_comboBox_model(QComboBox *cb);
    void slot_reset_combi();

    void slot_new_condi_row();


signals:
    void new_search_result(QList<int>);
    void new_search_result_sorted(QList<int>);
};

#endif // C_SEARCH_WIDGET_H
