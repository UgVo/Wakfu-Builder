#ifndef C_BUILD_DISPLAY_H
#define C_BUILD_DISPLAY_H

#include <QWidget>
#include "utilities/c_build.h"
#include "utilities/c_calcul.h"
#include "ui/c_item_viewer.h"
#include <QGraphicsDropShadowEffect>

namespace Ui {
class c_build_display;
}

class c_build_display : public QWidget
{
    Q_OBJECT

public:
    explicit c_build_display(QWidget *parent = nullptr);
    ~c_build_display();

    c_build build() const;
    void setBuild(const c_build &build);
public slots:
    void update_view();
    void equip_new_item(c_item item);
    void slot_second_hand_disabled(bool state);

private:
    Ui::c_build_display *ui;
    c_build _build;
    c_calcul calcul;
    QMap<QString,c_item_viewer*> item_position_map;

};

#endif // C_BUILD_DISPLAY_H
