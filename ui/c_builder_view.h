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
#include "utilities/c_io_manager.h"
#include "ui/c_aptitudes_display.h"

namespace Ui {
class c_builder_view;
}

class MainWindow;

class c_builder_view : public QWidget
{
    Q_OBJECT

public:
    explicit c_builder_view(c_dbmanager *_manager,QWidget *parent = nullptr);
    ~c_builder_view();

    c_status_build *getStatus_build() const;
    c_build_display *getBuild_display() const;
    c_elements_display *getElement_display() const;
    c_aptitudes_display *getAptitude_display() const;

    int getId() const;
    void setId(int value);

    QString getPath() const;
    void setPath(const QString &value);

    MainWindow *getParent() const;

    virtual void resizeEvent(QResizeEvent *event);

private:
    Ui::c_builder_view *ui;
    c_dbmanager *manager;
    c_build *build;
    c_result_display *result_display;
    c_status_build *status_build;
    c_elements_display *element_display;
    c_build_display *build_display;
    c_search_widget *search_widget;
    c_aptitudes_display *aptitude_display;
    int id; // -1 if comes or saved as a file, >0 if comes from or saved in the database, else 0
    QString path;
    MainWindow *parent;

    int state_column_number;

public slots:
    void slot_save(c_io_manager::jsonformat format, QString path = QString());
    bool slot_load(c_io_manager::jsonformat format, QString path = QString());
    bool slot_loadFrom(c_io_manager::jsonformat format, QString path_json);
    void slot_update(c_io_manager::jsonformat format);
//    virtual void keyPressEvent(QKeyEvent *event);
//    virtual void keyReleaseEvent(QKeyEvent *event);

signals:
    void shift_pressed(bool state);
};

#endif // C_BUILDER_VIEW_H
