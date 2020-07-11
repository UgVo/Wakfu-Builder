#ifndef C_STATUS_BUILD_H
#define C_STATUS_BUILD_H

#include <QWidget>
#include <QPixmap>
#include <QGraphicsDropShadowEffect>
#include <QDebug>
#include "ui.h"

namespace Ui {
class c_status_build;
}

class c_status_build : public QWidget
{
    Q_OBJECT

public:
    explicit c_status_build(QWidget *parent = nullptr);
    ~c_status_build();

    int getClasse() const;

private:
    Ui::c_status_build *ui;
    int classe;

public slots:
    void slot_enter_pressed();
    void setLvl(int lvl);
    void slot_bonus_changed();
    QString getName();
    int getLvl();
    void setName(QString name);
    bool isActivated_HM();
    bool isActivated_Nation();
    bool isActivated_Guilde();
    void Activated_HM(bool state);
    void Activated_Nation(bool state);
    void Activated_Guilde(bool state);
    void updateClass();
    void slot_class_clicked();
    void slot_class_changed(int id);

signals:
    void lvl_changed(int new_lvl);
    void bonus_changed(QList<bool> bonus);
    void show_class_popup();
};

#endif // C_STATUS_BUILD_H
