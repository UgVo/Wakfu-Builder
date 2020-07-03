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
    explicit c_build_display(c_build* build,QWidget *parent = nullptr);
    ~c_build_display();

    c_build* build() const;
    void setBuild(c_build* build);
public slots:
    void update_view();
    void equip_new_item(c_item item);
    void slot_second_hand_disabled(bool state);
    void slot_item_view_cliked(QString position);

signals:
    void load_search_position(QString position);

private:
    Ui::c_build_display *ui;
    c_build *_build;
    QMap<QString,c_item_viewer*> item_position_map;

};

#endif // C_BUILD_DISPLAY_H
