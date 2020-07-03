#ifndef C_RESULT_DISPLAY_H
#define C_RESULT_DISPLAY_H

#include <QWidget>
#include <QList>
#include <QStackedWidget>
#include <QStackedLayout>
#include <QMovie>
#include <QtConcurrent>
#include "utilities/c_item.h"
#include "utilities/utilities.h"
#include "utilities/c_item_model.h"
#include "utilities/c_dbmanager.h"
#include "ui/c_item_lite.h"
#include "ui/ui.h"
#include "ui/c_search_widget.h"
#include <QGraphicsDropShadowEffect>

namespace Ui {
class c_result_display;
}

class c_result_display : public QWidget
{
    Q_OBJECT

    int ROW_PER_PAGE = 13;
    int COLUMN_PER_PAGE = 3;

public:
    explicit c_result_display(c_dbmanager* _data_base, QWidget *parent = nullptr);
    ~c_result_display();

    void setUpWidget();
    void create_page(int number);
    void fill_page(int page);
    void empty_pages();
    void empty_page(int page);
    void hide_widgets();
    void clearLayout(QLayout* layout, bool deleteWidgets = true);
    //void clearItemListIfFinal();
    static c_item_lite* generate_item_lite(c_item item);

    virtual void resizeEvent(QResizeEvent *event);

    void refreshView();

private:
    Ui::c_result_display *ui;
    int page_number;
    c_dbmanager *data_base;
    int used_page_number;
    int current_page;
    int number_items;
    QList<int> id_list;
    QStackedWidget *stackedWidget;
    QStackedLayout *stacklayout;

    QLabel *loading;
    QMovie *movie;

    int index;
    bool sorted;

public slots:
    void slot_new_search_result(QList<int>);
    void slot_new_search_result_sorted(QList<int>);
    void slot_next();
    void slot_preview();
    void slot_item_doubleCliked(c_item item);

signals:
    void item_doubleCliked(c_item item);
};

#endif // C_RESULT_DISPLAY_H
