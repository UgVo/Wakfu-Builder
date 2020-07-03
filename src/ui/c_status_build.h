#ifndef C_STATUS_BUILD_H
#define C_STATUS_BUILD_H

#include <QWidget>
#include <QPixmap>
#include <QGraphicsDropShadowEffect>
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

private:
    Ui::c_status_build *ui;

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

signals:
    void lvl_changed(int new_lvl);
    void bonus_changed(QList<bool> bonus);
};

#endif // C_STATUS_BUILD_H
