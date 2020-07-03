#ifndef C_ENTRY_POINT_H
#define C_ENTRY_POINT_H

#include <QWidget>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <QMovie>
#include <QStackedLayout>
#include <QFileDialog>
#include "utilities/c_dbmanager.h"
#include "c_load_builder_dialog.h"
#include "ui/ui.h"
#include "utilities/c_io_manager.h"

class MainWindow;

namespace Ui {
class c_entry_point;
}

class c_entry_point : public QWidget
{
    Q_OBJECT

public:
    explicit c_entry_point(c_dbmanager *manager,QWidget *parent = nullptr);
    ~c_entry_point();
    virtual void resizeEvent(QResizeEvent *event);

private:
    Ui::c_entry_point *ui;

    QMovie *movie;
    MainWindow *parent;

    QParallelAnimationGroup* parralle_anim;
    QPropertyAnimation* animation1;
    QPropertyAnimation* animation2;
    QPropertyAnimation* animation3;
    QPropertyAnimation* animation4;
    QPropertyAnimation* animation5;
    QGraphicsOpacityEffect *effect1;
    QGraphicsOpacityEffect *effect2;

    int anim_duration_ms;
    c_load_builder_dialog *load_builder;
    c_dbmanager *manager;
    QFileDialog *file_dial;

    int state;
    qreal movie_aspect;
    c_io_manager::jsonformat format;
    QString path_json;
    int id;

public slots:
    void slot_open_button();
    void slot_new_button();
    void slot_first_anim_finished();
    void slot_creation_builder_anim();
    void slot_second_anim_finished();
    void slot_open_from_source();
    void slot_cancel_open();
    void slot_open_animation_finished();

signals:
    void open_clicked();
    void new_clicked();
    void manage_movie(bool play);
    void first_animation_finished();
    void second_animation_finished();
    void load_builder_from(const c_io_manager::jsonformat, QString,int);
};

#endif // C_ENTRY_POINT_H
