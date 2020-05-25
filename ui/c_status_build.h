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

signals:
    void lvl_changed(int new_lvl);
};

#endif // C_STATUS_BUILD_H
