#include "c_entry_point.h"
#include "ui_c_entry_point.h"
#include "mainwindow.h"

c_entry_point::c_entry_point(QWidget *_parent) :
    QWidget(_parent),
    ui(new Ui::c_entry_point)
{
    ui->setupUi(this);
    parent = static_cast<MainWindow*>(_parent);
    anim_duration_ms = 1500;
    QObject::connect(ui->pushButton_new_build,&QPushButton::clicked,this,&c_entry_point::slot_new_button);
    QObject::connect(ui->pushButton_open_build,&QPushButton::clicked,this,&c_entry_point::slot_open_button);
    movie = new QMovie("resources/divers/eliacubeHD.gif");
    ui->background_eliacube->setMovie(movie);
    ui->background_eliacube->setAlignment(Qt::AlignCenter);
    ui->background_eliacube->show();
    movie->start();
    static_cast<QStackedLayout*>(ui->stackedWidget_entry_point->layout())->setStackingMode(QStackedLayout::StackAll);
    ui->label_creation_builder->setText("");
    ui->label_creation_builder->setStyleSheet("color:white");
    ui->stackedWidget_entry_point->setCurrentIndex(0);
}

c_entry_point::~c_entry_point()
{
    delete ui;
}

void c_entry_point::resizeEvent(QResizeEvent * /*event*/) {
    QRect rect = this->rect();
    QPoint p_pb_new_build((rect.width()-506)/2,(rect.height()-172)/2);
    QPoint p_pb_open_build = p_pb_new_build + QPoint(256,0);
    QPoint p_label_creation_builder((rect.width()-106)/2,(rect.height()-172)/2 + 156);
    QPoint p_w_file((rect.width()-1210)/2,rect.height());
    QPoint p_w_bdd((rect.width()-1210)/2 + 610,rect.height());
    ui->pushButton_new_build->move(p_pb_new_build);
    ui->pushButton_open_build->move(p_pb_open_build);
    ui->label_creation_builder->move(p_label_creation_builder);
    ui->frame_bdd->move(p_w_bdd);
    ui->frame_file->move(p_w_file);
}

void c_entry_point::slot_open_button() {
    ui->pushButton_open_build->raise();
    QPoint translation = QPoint(((ui->pushButton_new_build->width()*2)+6)/2 - ui->pushButton_new_build->width()/2,0);
    animation1 = new QPropertyAnimation(ui->pushButton_new_build,"geometry");
    animation1->setDuration(anim_duration_ms);
    QRect rect_button_new_p0 = ui->pushButton_new_build->rect();
    QPoint position_button_new_0 = ui->pushButton_new_build->pos();
    rect_button_new_p0.setTopLeft(position_button_new_0);
    animation1->setKeyValueAt(0,rect_button_new_p0);
    animation1->setKeyValueAt(0.5,rect_button_new_p0);
    rect_button_new_p0.setTopLeft(position_button_new_0 + translation);
    animation1->setKeyValueAt(1,rect_button_new_p0);
    animation1->setEasingCurve(QEasingCurve::InOutQuad);

    animation2 = new QPropertyAnimation(ui->pushButton_open_build,"geometry");
    animation2->setDuration(anim_duration_ms);
    QRect rect_button_p0 = ui->pushButton_open_build->rect();
    QPoint position_button_0 = ui->pushButton_open_build->pos();
    ui->pushButton_open_build->move(position_button_0);
    rect_button_p0.setTopLeft(position_button_0);
    animation2->setKeyValueAt(0,rect_button_p0);
    animation2->setKeyValueAt(0.5,rect_button_p0);
    rect_button_p0.setTopLeft(position_button_0 - translation);
    animation2->setKeyValueAt(1,rect_button_p0);
    animation2->setEasingCurve(QEasingCurve::InOutQuad);

    parralle_anim = new QParallelAnimationGroup;
    parralle_anim->addAnimation(animation1);
    parralle_anim->addAnimation(animation2);

    parralle_anim->start();
}

void c_entry_point::slot_new_button() {
    ui->label_creation_builder->setText("Création du builder ...");

    effect1 = new QGraphicsOpacityEffect(ui->background_eliacube);
    ui->background_eliacube->setGraphicsEffect(effect1);
    animation1 = new QPropertyAnimation(effect1, "opacity");
    animation1->setDuration(anim_duration_ms);
    animation1->setStartValue(1.0);
    animation1->setEndValue(0.0);
    animation1->setEasingCurve(QEasingCurve::OutQuad);
    qDebug() << "anim1";

    effect2 = new QGraphicsOpacityEffect(ui->pushButton_open_build);
    ui->pushButton_open_build->setGraphicsEffect(effect2);
    animation2 = new QPropertyAnimation(effect2, "opacity");
    animation2->setDuration(anim_duration_ms);
    animation2->setStartValue(1.0);
    animation2->setEndValue(0.0);
    animation2->setEasingCurve(QEasingCurve::OutQuad);
    qDebug() << "anim2";

    ui->pushButton_new_build->raise();
    QPoint translation = QPoint(((ui->pushButton_new_build->width()*2)+6)/2 - ui->pushButton_new_build->width()/2,0);
    animation3 = new QPropertyAnimation(ui->pushButton_new_build,"geometry");
    animation3->setDuration(anim_duration_ms);
    QRect rect_button_new_p0 = ui->pushButton_new_build->rect();
    QPoint position_button_new_0 = ui->pushButton_new_build->pos();
    rect_button_new_p0.setTopLeft(position_button_new_0);
    animation3->setKeyValueAt(0,rect_button_new_p0);
    animation3->setKeyValueAt(0.5,rect_button_new_p0);
    rect_button_new_p0.setTopLeft(position_button_new_0 + translation);
    animation3->setKeyValueAt(1,rect_button_new_p0);
    animation3->setEasingCurve(QEasingCurve::InOutQuad);
    qDebug() << "anim3";

    animation4 = new QPropertyAnimation(ui->pushButton_open_build,"geometry");
    animation4->setDuration(anim_duration_ms);
    QRect rect_button_p0 = ui->pushButton_open_build->rect();
    QPoint position_button_0 = ui->pushButton_open_build->pos();
    rect_button_p0.setTopLeft(position_button_0);
    animation4->setKeyValueAt(0,rect_button_p0);
    animation4->setKeyValueAt(0.5,rect_button_p0);
    rect_button_p0.setTopLeft(position_button_0 - translation);
    animation4->setKeyValueAt(1,rect_button_p0);
    animation4->setEasingCurve(QEasingCurve::InOutQuad);
    qDebug() << "anim4";

    parralle_anim = new QParallelAnimationGroup;
    parralle_anim->addAnimation(animation1);
    parralle_anim->addAnimation(animation2);
    parralle_anim->addAnimation(animation3);
    parralle_anim->addAnimation(animation4);

    parralle_anim->start(QParallelAnimationGroup::DeleteWhenStopped);

    QObject::connect(parralle_anim,&QParallelAnimationGroup::finished,this,&c_entry_point::slot_first_anim_finished);
}

void c_entry_point::slot_first_anim_finished() {
    ui->pushButton_open_build->hide();
    emit first_animation_finished();
}

void c_entry_point::slot_creation_builder_anim() {
    effect2 = new QGraphicsOpacityEffect(this);
    this->setGraphicsEffect(effect2);
    animation2 = new QPropertyAnimation(effect2, "opacity");
    animation2->setDuration(anim_duration_ms);
    animation2->setStartValue(1.0);
    animation2->setEndValue(0.0);
    animation2->setEasingCurve(QEasingCurve::OutQuad);
    qDebug() << "anim5";

    QPoint translation = QPoint(0,this->height());
    animation3 = new QPropertyAnimation(this,"geometry");
    animation3->setDuration(anim_duration_ms);
    QRect rect_button_new_p0 = this->rect();
    QPoint position_button_new_0 = this->pos();
    rect_button_new_p0.setTopLeft(position_button_new_0);
    animation3->setKeyValueAt(0,rect_button_new_p0);
    rect_button_new_p0.setTopLeft(position_button_new_0 + translation);
    animation3->setKeyValueAt(1,rect_button_new_p0);
    animation3->setEasingCurve(QEasingCurve::InOutQuad);
    qDebug() << "anim6";

    parralle_anim = new QParallelAnimationGroup;
    parralle_anim->addAnimation(animation2);
    parralle_anim->addAnimation(animation3);

    parralle_anim->start(QParallelAnimationGroup::DeleteWhenStopped);

    QObject::connect(parralle_anim,&QParallelAnimationGroup::finished,this,&c_entry_point::slot_second_anim_finished);
}

void c_entry_point::slot_second_anim_finished() {
    qDebug() << "anim7";
    emit second_animation_finished();
}
