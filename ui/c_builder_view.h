#ifndef C_BUILDER_VIEW_H
#define C_BUILDER_VIEW_H

#include <QWidget>
#include "utilities/c_dbmanager.h"
#include "utilities/c_build.h"
#include "ui/c_result_display.h"
#include "ui/c_status_build.h"
#include "ui/c_elements_display.h"
#include "ui/c_build_display.h"
#include "ui/c_search_widget.h"

namespace Ui {
class c_builder_view;
}

class c_builder_view : public QWidget
{
    Q_OBJECT

public:
    explicit c_builder_view(c_dbmanager *_manager,QWidget *parent = nullptr);
    ~c_builder_view();

private:
    Ui::c_builder_view *ui;
    c_dbmanager *manager;
    c_build *build;
    c_result_display *result_display;
    c_status_build *status_build;
    c_elements_display *element_display;
    c_build_display *build_display;
    c_search_widget *search_widget;
};

#endif // C_BUILDER_VIEW_H
