#ifndef C_APTITUDES_DISPLAY_H
#define C_APTITUDES_DISPLAY_H

#include <QWidget>
#include <QMap>
#include <QString>
#include <QDebug>
#include <QLabel>
#include "ui.h"
#include "c_aptitude_unite.h"

class c_builder_view;

namespace Ui {
class c_aptitudes_display;
}

class c_aptitudes_display : public QWidget
{
    Q_OBJECT

public:
    explicit c_aptitudes_display(QWidget *parent = nullptr);
    ~c_aptitudes_display();
    int decrease(QString section);
    int increase(QString section);
    void compute_counts();

private:
    Ui::c_aptitudes_display *ui;
    QMap<QString,int> counts;
    QMap<QString,QList<c_aptitude_unite*>*> map_unites;
    QMap<QString,c_aptitude_unite*> map_unites_all;
    QMap<QString,QLabel*> map_counts_labels;

    c_builder_view *parent;
    int lvl;

public slots:
    void setLvl(int lvl);
    void reset();
    void slot_value_changed(int value, QString type);
    void slot_set_aptitudes(QMap<QString,int> bonuses);

signals:
    void value_changed(QString type, int value);

};

#endif // C_APTITUDES_DISPLAY_H
