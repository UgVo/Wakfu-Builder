#include "c_entry_point.h"
#include "ui_c_entry_point.h"
#include "mainwindow.h"

c_entry_point::c_entry_point(c_dbmanager *_manager, QWidget *_parent) :
    QWidget(_parent), ui(new Ui::c_entry_point), parent(static_cast<MainWindow*>(_parent)), manager(_manager)
{
    ui->setupUi(this);
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

    state = 0;
    movie_aspect = (1920.0)/1080.0;

    file_dial = nullptr;
    load_builder = nullptr;
}

c_entry_point::~c_entry_point()
{
    delete ui;
}

void c_entry_point::resizeEvent(QResizeEvent * /*event*/) {
    int width = int(qreal(this->size().height()) * movie_aspect);
    QSize movie_size;
    if (width <= this->size().width()) {
        movie_size = QSize(width,this->size().height());
    } else {
        int height = int(qreal(this->size().width()) / movie_aspect);
        movie_size = QSize(this->size().width(),height);
    }
    QRect rect = this->rect();
    ui->background_eliacube->move((rect.width()-movie_size.width())/2,(rect.height()-movie_size.height())/2);
    ui->background_eliacube->resize(movie_size);
    movie->setScaledSize(movie_size);
    QPoint p_pb_new_build;
    QPoint p_pb_open_build;
    QPoint p_label_creation_builder;
    QPoint p_w_file;
    QPoint p_w_bdd;
    if (state == 0) {
        p_pb_new_build = QPoint((rect.width()-506)/2,(rect.height()-172)/2);
        p_pb_open_build = p_pb_new_build + QPoint(256,0);
        p_label_creation_builder = QPoint((rect.width()-106)/2,(rect.height()-172)/2 + 156);
        p_w_file = QPoint((rect.width()-1210)/2,rect.height());
        p_w_bdd = QPoint((rect.width()-1210)/2 + 610,rect.height());
    } else if (state == 1) {
        p_pb_new_build = QPoint((rect.width()-250)/2,(rect.height()-172)/2);
        p_pb_open_build = p_pb_new_build;
        p_label_creation_builder = QPoint((rect.width()-106)/2,(rect.height()-172)/2 + 156);
        p_w_file = QPoint((rect.width()-1210)/2,rect.height());
        p_w_bdd = QPoint((rect.width()-1210)/2 + 610,rect.height());
    } else if (state == 2) {
        p_w_file= QPoint((rect.width()-1210)/2,(rect.height()-150-400+20)/2 + 170);
        p_w_bdd = QPoint((rect.width()-1210)/2 + 610,(rect.height()-150-400+20)/2 + 170);
        p_pb_new_build = QPoint(20,20);
        p_pb_open_build = QPoint((rect.width()-250)/2,(rect.height()-150-400+20)/2);
        p_label_creation_builder = QPoint((rect.width()-120)/2,(rect.height()-172)/2 + 156);
    }
    ui->pushButton_new_build->move(p_pb_new_build);
    ui->pushButton_open_build->move(p_pb_open_build);
    ui->label_creation_builder->move(p_label_creation_builder);
    ui->frame_bdd->move(p_w_bdd);
    ui->frame_file->move(p_w_file);
}

void c_entry_point::slot_open_button() {

    if (state == 0) {
        ui->pushButton_open_build->raise();
        if (load_builder == nullptr) {
            load_builder = new c_load_builder_dialog(manager,this);
            load_builder->setStyleSheet(QString("c_load_builder_dialog {background-color:%1; border-radius:3px;}").arg(app_color::grey_blue));
            ui->verticalLayout_bdd->addWidget(load_builder);
            QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(ui->frame_bdd);
            shadow->setColor(QColor(91, 108, 142, 180));
            shadow->setOffset(2,2);
            ui->frame_bdd->setGraphicsEffect(shadow);
            QObject::connect(load_builder,&c_load_builder_dialog::accepted,this,&c_entry_point::slot_open_from_source);
        }
        if (file_dial == nullptr) {
            file_dial = new QFileDialog(this,tr("Save Build"), parent->getApp_path() + "/save", tr("Json files (*.json)"));
            file_dial->setStyleSheet(QString("QFileDialog{ background-color:%1; border-radius:3px;}").arg(app_color::grey_blue));
            ui->verticalLayout_file->addWidget(file_dial);
            QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(ui->frame_file);
            shadow->setColor(QColor(91, 108, 142, 180));
            shadow->setOffset(2,2);
            ui->frame_file->setGraphicsEffect(shadow);
            QObject::connect(file_dial,&QFileDialog::accepted,this,&c_entry_point::slot_open_from_source);
        }

        QRect rect = this->rect();
        QPoint p_w_file((rect.width()-1210)/2,rect.height());
        QPoint p_w_file_final((rect.width()-1210)/2,(rect.height()-150-400+20)/2 + 170);
        QPoint p_w_bdd((rect.width()-1210)/2 + 610,rect.height());
        QPoint p_w_bdd_final((rect.width()-1210)/2 + 610,(rect.height()-150-400+20)/2 + 170);
        QPoint p_pb_new_build((rect.width()-506)/2,(rect.height()-172)/2);
        QPoint p_pb_new_build_final(20,20);
        QPoint p_pb_open_build((rect.width()-506)/2 + 256,(rect.height()-172)/2);
        QPoint p_pb_open_build_final((rect.width()-250)/2,(rect.height()-150-400+20)/2);

        animation1 = new QPropertyAnimation(ui->pushButton_new_build,"geometry");
        animation1->setDuration(anim_duration_ms);
        QRect rect_button_new = ui->pushButton_new_build->rect();
        rect_button_new.setTopLeft(p_pb_new_build);
        animation1->setKeyValueAt(0,rect_button_new);
        animation1->setKeyValueAt(0.5,rect_button_new);
        rect_button_new.setTopLeft(p_pb_new_build_final);
        animation1->setKeyValueAt(1,rect_button_new);
        animation1->setEasingCurve(QEasingCurve::InOutQuad);

        ui->pushButton_new_build->setMinimumSize(ui->pushButton_new_build->size()/2);
        animation2 = new QPropertyAnimation(ui->pushButton_new_build,"size");
        animation2->setDuration(anim_duration_ms);
        QSize size_button_new_size = ui->pushButton_new_build->size()/2;
        animation2->setKeyValueAt(0,ui->pushButton_new_build->size());
        animation2->setKeyValueAt(0.5,ui->pushButton_new_build->size());
        animation2->setKeyValueAt(1,size_button_new_size);
        animation2->setEasingCurve(QEasingCurve::InOutQuad);

        animation3 = new QPropertyAnimation(ui->pushButton_open_build,"geometry");
        animation3->setDuration(anim_duration_ms);
        QRect rect_button_open = ui->pushButton_open_build->rect();
        rect_button_open.setTopLeft(p_pb_open_build);
        animation3->setKeyValueAt(0,rect_button_open);
        animation3->setKeyValueAt(0.5,rect_button_open);
        rect_button_open.setTopLeft(p_pb_open_build_final);
        animation3->setKeyValueAt(1,rect_button_open);
        animation3->setEasingCurve(QEasingCurve::InOutQuad);

        animation4 = new QPropertyAnimation(ui->frame_bdd,"geometry");
        animation4->setDuration(anim_duration_ms);
        QRect rect_bdd = ui->frame_bdd->rect();
        rect_bdd.setTopLeft(p_w_bdd);
        animation4->setKeyValueAt(0,rect_bdd);
        animation4->setKeyValueAt(0.5,rect_bdd);
        rect_bdd.setTopLeft(p_w_bdd_final);
        animation4->setKeyValueAt(1,rect_bdd);
        animation4->setEasingCurve(QEasingCurve::InOutQuad);

        animation5 = new QPropertyAnimation(ui->frame_file,"geometry");
        animation5->setDuration(anim_duration_ms);
        QRect rect_file = ui->frame_file->rect();
        rect_file.setTopLeft(p_w_file);
        animation5->setKeyValueAt(0,rect_file);
        animation5->setKeyValueAt(0.5,rect_file);
        rect_file.setTopLeft(p_w_file_final);
        animation5->setKeyValueAt(1,rect_file);
        animation5->setEasingCurve(QEasingCurve::InOutQuad);

        parralle_anim = new QParallelAnimationGroup;
        parralle_anim->addAnimation(animation1);
        parralle_anim->addAnimation(animation2);
        parralle_anim->addAnimation(animation3);
        parralle_anim->addAnimation(animation4);
        parralle_anim->addAnimation(animation5);

        parralle_anim->start(QParallelAnimationGroup::DeleteWhenStopped);

        state = 2;

        QObject::connect(file_dial,&QFileDialog::rejected,this,&c_entry_point::slot_cancel_open);
        QObject::connect(load_builder,&c_load_builder_dialog::rejected,this,&c_entry_point::slot_cancel_open);
    }
}

void c_entry_point::slot_new_button() {

    if (state == 0) {
        QRect rect = this->rect();
        QPoint p_pb_new_build((rect.width()-506)/2,(rect.height()-172)/2);
        QPoint p_pb_new_build_final((rect.width()-250)/2,(rect.height()-172)/2);
        QPoint p_pb_open_build((rect.width()-506)/2 + 256,(rect.height()-172)/2);
        QPoint p_pb_open_build_final = p_pb_new_build_final;

        ui->label_creation_builder->setText("Création du builder ...");
        ui->pushButton_new_build->setMinimumSize(QSize(250,150));

        effect1 = new QGraphicsOpacityEffect(ui->background_eliacube);
        ui->background_eliacube->setGraphicsEffect(effect1);
        animation1 = new QPropertyAnimation(effect1, "opacity");
        animation1->setDuration(anim_duration_ms);
        animation1->setStartValue(1.0);
        animation1->setEndValue(0.0);
        animation1->setEasingCurve(QEasingCurve::OutQuad);

        effect2 = new QGraphicsOpacityEffect(ui->pushButton_open_build);
        ui->pushButton_open_build->setGraphicsEffect(effect2);
        animation2 = new QPropertyAnimation(effect2, "opacity");
        animation2->setDuration(anim_duration_ms);
        animation2->setStartValue(1.0);
        animation2->setEndValue(0.0);
        animation2->setEasingCurve(QEasingCurve::OutQuad);

        ui->pushButton_new_build->raise();
        animation3 = new QPropertyAnimation(ui->pushButton_new_build,"geometry");
        animation3->setDuration(anim_duration_ms);
        QRect rect_button_new = ui->pushButton_new_build->rect();
        rect_button_new.setTopLeft(p_pb_new_build);
        animation3->setKeyValueAt(0,rect_button_new);
        animation3->setKeyValueAt(0.5,rect_button_new);
        rect_button_new.setTopLeft(p_pb_new_build_final);
        animation3->setKeyValueAt(1,rect_button_new);
        animation3->setEasingCurve(QEasingCurve::InOutQuad);

        animation4 = new QPropertyAnimation(ui->pushButton_open_build,"geometry");
        animation4->setDuration(anim_duration_ms);
        QRect rect_button_open = ui->pushButton_open_build->rect();
        rect_button_open.setTopLeft(p_pb_open_build);
        animation4->setKeyValueAt(0,rect_button_open);
        animation4->setKeyValueAt(0.5,rect_button_open);
        rect_button_open.setTopLeft(p_pb_open_build_final);
        animation4->setKeyValueAt(1,rect_button_open);
        animation4->setEasingCurve(QEasingCurve::InOutQuad);

        parralle_anim = new QParallelAnimationGroup;
        parralle_anim->addAnimation(animation1);
        parralle_anim->addAnimation(animation2);
        parralle_anim->addAnimation(animation3);
        parralle_anim->addAnimation(animation4);

        parralle_anim->start(QParallelAnimationGroup::DeleteWhenStopped);

        QObject::connect(parralle_anim,&QParallelAnimationGroup::finished,this,&c_entry_point::slot_first_anim_finished);

        state = 1;
    } else if (state == 2) {

        QRect rect = this->rect();
        QPoint p_w_file_final((rect.width()-1210)/2,rect.height());
        QPoint p_w_file((rect.width()-1210)/2,(rect.height()-150-400+20)/2 + 170);
        QPoint p_w_bdd_final((rect.width()-1210)/2 + 610,rect.height());
        QPoint p_w_bdd((rect.width()-1210)/2 + 610,(rect.height()-150-400+20)/2 + 170);
        QPoint p_pb_new_build_final((rect.width()-506)/2,(rect.height()-172)/2);
        QPoint p_pb_new_build(20,20);
        QPoint p_pb_open_build_final((rect.width()-506)/2 + 256,(rect.height()-172)/2);
        QPoint p_pb_open_build((rect.width()-250)/2,(rect.height()-150-400+20)/2);

        animation1 = new QPropertyAnimation(ui->pushButton_new_build,"geometry");
        animation1->setDuration(anim_duration_ms);
        QRect rect_button_new = ui->pushButton_new_build->rect();
        rect_button_new.setTopLeft(p_pb_new_build);
        animation1->setKeyValueAt(0,rect_button_new);
        animation1->setKeyValueAt(0.5,rect_button_new);
        rect_button_new.setTopLeft(p_pb_new_build_final);
        animation1->setKeyValueAt(1,rect_button_new);
        animation1->setEasingCurve(QEasingCurve::InOutQuad);

        animation2 = new QPropertyAnimation(ui->pushButton_new_build,"size");
        animation2->setDuration(anim_duration_ms);
        QSize size_button_new_size = ui->pushButton_new_build->size()*2;
        animation2->setKeyValueAt(0,ui->pushButton_new_build->size());
        animation2->setKeyValueAt(0.5,ui->pushButton_new_build->size());
        animation2->setKeyValueAt(1,size_button_new_size);
        animation2->setEasingCurve(QEasingCurve::InOutQuad);

        animation3 = new QPropertyAnimation(ui->pushButton_open_build,"geometry");
        animation3->setDuration(anim_duration_ms);
        QRect rect_button_open = ui->pushButton_open_build->rect();
        rect_button_open.setTopLeft(p_pb_open_build);
        animation3->setKeyValueAt(0,rect_button_open);
        animation3->setKeyValueAt(0.5,rect_button_open);
        rect_button_open.setTopLeft(p_pb_open_build_final);
        animation3->setKeyValueAt(1,rect_button_open);
        animation3->setEasingCurve(QEasingCurve::InOutQuad);

        animation4 = new QPropertyAnimation(ui->frame_bdd,"geometry");
        animation4->setDuration(anim_duration_ms);
        QRect rect_bdd = ui->frame_bdd->rect();
        rect_bdd.setTopLeft(p_w_bdd);
        animation4->setKeyValueAt(0,rect_bdd);
        animation4->setKeyValueAt(0.5,rect_bdd);
        rect_bdd.setTopLeft(p_w_bdd_final);
        animation4->setKeyValueAt(1,rect_bdd);
        animation4->setEasingCurve(QEasingCurve::InOutQuad);

        animation5 = new QPropertyAnimation(ui->frame_file,"geometry");
        animation5->setDuration(anim_duration_ms);
        QRect rect_file = ui->frame_file->rect();
        rect_file.setTopLeft(p_w_file);
        animation5->setKeyValueAt(0,rect_file);
        animation5->setKeyValueAt(0.5,rect_file);
        rect_file.setTopLeft(p_w_file_final);
        animation5->setKeyValueAt(1,rect_file);
        animation5->setEasingCurve(QEasingCurve::InOutQuad);

        parralle_anim = new QParallelAnimationGroup;
        parralle_anim->addAnimation(animation1);
        parralle_anim->addAnimation(animation2);
        parralle_anim->addAnimation(animation3);
        parralle_anim->addAnimation(animation4);
        parralle_anim->addAnimation(animation5);

        parralle_anim->start(QParallelAnimationGroup::DeleteWhenStopped);

        state = 0;

        QObject::connect(parralle_anim,&QParallelAnimationGroup::finished,this,&c_entry_point::slot_new_button);
    }
}

void c_entry_point::slot_first_anim_finished() {
    ui->pushButton_open_build->hide();
    state = 1;
    emit first_animation_finished();
}

void c_entry_point::slot_creation_builder_anim() {
    ui->label_creation_builder->hide();
    QRect rect = this->rect();
    QPoint p_pb_new_build((rect.width()-250)/2,(rect.height()-172)/2);
    QPoint p_pb_new_build_final((rect.width()-250)/2,rect.height());

    effect2 = new QGraphicsOpacityEffect(this);
    this->setGraphicsEffect(effect2);
    animation2 = new QPropertyAnimation(effect2, "opacity");
    animation2->setDuration(anim_duration_ms);
    animation2->setStartValue(1.0);
    animation2->setEndValue(0.0);
    animation2->setEasingCurve(QEasingCurve::OutQuad);

    animation4 = new QPropertyAnimation(ui->pushButton_new_build,"geometry");
    animation4->setDuration(anim_duration_ms);
    QRect rect_button_new = ui->pushButton_new_build->rect();
    rect_button_new.setTopLeft(p_pb_new_build);
    animation4->setKeyValueAt(0,rect_button_new);
    rect_button_new.setTopLeft(p_pb_new_build_final);
    animation4->setKeyValueAt(1,rect_button_new);
    animation4->setEasingCurve(QEasingCurve::InOutQuad);

    animation1 = new QPropertyAnimation(ui->pushButton_open_build,"geometry");
    animation1->setDuration(anim_duration_ms);
    rect_button_new.setTopLeft(p_pb_new_build);
    animation1->setKeyValueAt(0,rect_button_new);
    rect_button_new.setTopLeft(p_pb_new_build_final);
    animation1->setKeyValueAt(1,rect_button_new);
    animation1->setEasingCurve(QEasingCurve::InOutQuad);

    parralle_anim = new QParallelAnimationGroup;
    parralle_anim->addAnimation(animation2);
    parralle_anim->addAnimation(animation4);
    parralle_anim->addAnimation(animation1);

    parralle_anim->start(QParallelAnimationGroup::DeleteWhenStopped);

    QObject::connect(parralle_anim,&QParallelAnimationGroup::finished,this,&c_entry_point::slot_second_anim_finished);
}

void c_entry_point::slot_second_anim_finished() {
    emit second_animation_finished();
}

void c_entry_point::slot_open_from_source() {
    qDebug() << "accepted";
    qDebug() << sender()->metaObject()->className();
    QObject* sender_widget = sender();
    QRect rect = this->rect();
    QPoint p_w_file_final((rect.width()-1210)/2,rect.height());
    QPoint p_w_file((rect.width()-1210)/2,(rect.height()-150-400+20)/2 + 170);
    QPoint p_w_bdd_final((rect.width()-1210)/2 + 610,rect.height());
    QPoint p_w_bdd((rect.width()-1210)/2 + 610,(rect.height()-150-400+20)/2 + 170);
    QPoint p_pb_open_build_final((rect.width()-250)/2,(rect.height()-172)/2);
    QPoint p_pb_open_build((rect.width()-250)/2,(rect.height()-150-400+20)/2);
    if (dynamic_cast<QFileDialog*>(sender_widget) != nullptr) {
        format = c_io_manager::jsonformat::file;
        path_json = file_dial->selectedFiles().at(0);
        id = -1;
    } else {
        format = c_io_manager::jsonformat::database;
        path_json = load_builder->getCurrent_json();
        id = load_builder->getCurrent_id();
    }
    load_builder->show();
    file_dial->show();

    effect2 = new QGraphicsOpacityEffect(ui->pushButton_new_build);
    ui->pushButton_new_build->setGraphicsEffect(effect2);
    animation1 = new QPropertyAnimation(effect2, "opacity");
    animation1->setDuration(anim_duration_ms);
    animation1->setStartValue(1.0);
    animation1->setEndValue(0.0);
    animation1->setEasingCurve(QEasingCurve::OutQuad);

    animation2 = new QPropertyAnimation(ui->frame_bdd,"geometry");
    animation2->setDuration(anim_duration_ms);
    QRect rect_bdd = ui->frame_bdd->rect();
    rect_bdd.setTopLeft(p_w_bdd);
    animation2->setKeyValueAt(0,rect_bdd);
    animation2->setKeyValueAt(0.5,rect_bdd);
    rect_bdd.setTopLeft(p_w_bdd_final);
    animation2->setKeyValueAt(1,rect_bdd);
    animation2->setEasingCurve(QEasingCurve::InOutQuad);

    animation3 = new QPropertyAnimation(ui->frame_file,"geometry");
    animation3->setDuration(anim_duration_ms);
    QRect rect_file = ui->frame_file->rect();
    rect_file.setTopLeft(p_w_file);
    animation3->setKeyValueAt(0,rect_file);
    animation3->setKeyValueAt(0.5,rect_file);
    rect_file.setTopLeft(p_w_file_final);
    animation3->setKeyValueAt(1,rect_file);
    animation3->setEasingCurve(QEasingCurve::InOutQuad);

    animation4 = new QPropertyAnimation(ui->pushButton_open_build,"geometry");
    animation4->setDuration(anim_duration_ms);
    QRect rect_button_open = ui->pushButton_open_build->rect();
    rect_button_open.setTopLeft(p_pb_open_build);
    animation4->setKeyValueAt(0,rect_button_open);
    animation4->setKeyValueAt(0.5,rect_button_open);
    rect_button_open.setTopLeft(p_pb_open_build_final);
    animation4->setKeyValueAt(1,rect_button_open);
    animation4->setEasingCurve(QEasingCurve::InOutQuad);

    effect1 = new QGraphicsOpacityEffect(ui->background_eliacube);
    ui->background_eliacube->setGraphicsEffect(effect1);
    animation5 = new QPropertyAnimation(effect1, "opacity");
    animation5->setDuration(anim_duration_ms);
    animation5->setStartValue(1.0);
    animation5->setEndValue(0.0);
    animation5->setEasingCurve(QEasingCurve::OutQuad);

    parralle_anim = new QParallelAnimationGroup;
    parralle_anim->addAnimation(animation1);
    parralle_anim->addAnimation(animation2);
    parralle_anim->addAnimation(animation3);
    parralle_anim->addAnimation(animation4);
    parralle_anim->addAnimation(animation5);

    parralle_anim->start(QParallelAnimationGroup::DeleteWhenStopped);

    ui->label_creation_builder->setText("Ouverture du builder...");
    ui->label_creation_builder->hide();
    QObject::connect(parralle_anim,&QParallelAnimationGroup::finished,ui->pushButton_new_build,&QPushButton::hide);
    QObject::connect(parralle_anim,&QParallelAnimationGroup::finished,ui->label_creation_builder,&QLabel::show);
    QObject::connect(parralle_anim,&QParallelAnimationGroup::finished,this,&c_entry_point::slot_open_animation_finished);
}

void c_entry_point::slot_cancel_open() {
    load_builder->show();
    file_dial->show();

    QRect rect = this->rect();
    QPoint p_w_file_final((rect.width()-1210)/2,rect.height());
    QPoint p_w_file((rect.width()-1210)/2,(rect.height()-150-400+20)/2 + 170);
    QPoint p_w_bdd_final((rect.width()-1210)/2 + 610,rect.height());
    QPoint p_w_bdd((rect.width()-1210)/2 + 610,(rect.height()-150-400+20)/2 + 170);
    QPoint p_pb_new_build_final((rect.width()-506)/2,(rect.height()-172)/2);
    QPoint p_pb_new_build(20,20);
    QPoint p_pb_open_build_final((rect.width()-506)/2 + 256,(rect.height()-172)/2);
    QPoint p_pb_open_build((rect.width()-250)/2,(rect.height()-150-400+20)/2);

    animation1 = new QPropertyAnimation(ui->pushButton_new_build,"geometry");
    animation1->setDuration(anim_duration_ms);
    QRect rect_button_new = ui->pushButton_new_build->rect();
    rect_button_new.setTopLeft(p_pb_new_build);
    animation1->setKeyValueAt(0,rect_button_new);
    animation1->setKeyValueAt(0.5,rect_button_new);
    rect_button_new.setTopLeft(p_pb_new_build_final);
    animation1->setKeyValueAt(1,rect_button_new);
    animation1->setEasingCurve(QEasingCurve::InOutQuad);

    animation2 = new QPropertyAnimation(ui->pushButton_new_build,"size");
    animation2->setDuration(anim_duration_ms);
    QSize size_button_new_size = ui->pushButton_new_build->size()*2;
    animation2->setKeyValueAt(0,ui->pushButton_new_build->size());
    animation2->setKeyValueAt(0.5,ui->pushButton_new_build->size());
    animation2->setKeyValueAt(1,size_button_new_size);
    animation2->setEasingCurve(QEasingCurve::InOutQuad);

    animation3 = new QPropertyAnimation(ui->pushButton_open_build,"geometry");
    animation3->setDuration(anim_duration_ms);
    QRect rect_button_open = ui->pushButton_open_build->rect();
    rect_button_open.setTopLeft(p_pb_open_build);
    animation3->setKeyValueAt(0,rect_button_open);
    animation3->setKeyValueAt(0.5,rect_button_open);
    rect_button_open.setTopLeft(p_pb_open_build_final);
    animation3->setKeyValueAt(1,rect_button_open);
    animation3->setEasingCurve(QEasingCurve::InOutQuad);

    animation4 = new QPropertyAnimation(ui->frame_bdd,"geometry");
    animation4->setDuration(anim_duration_ms);
    QRect rect_bdd = ui->frame_bdd->rect();
    rect_bdd.setTopLeft(p_w_bdd);
    animation4->setKeyValueAt(0,rect_bdd);
    animation4->setKeyValueAt(0.5,rect_bdd);
    rect_bdd.setTopLeft(p_w_bdd_final);
    animation4->setKeyValueAt(1,rect_bdd);
    animation4->setEasingCurve(QEasingCurve::InOutQuad);

    animation5 = new QPropertyAnimation(ui->frame_file,"geometry");
    animation5->setDuration(anim_duration_ms);
    QRect rect_file = ui->frame_file->rect();
    rect_file.setTopLeft(p_w_file);
    animation5->setKeyValueAt(0,rect_file);
    animation5->setKeyValueAt(0.5,rect_file);
    rect_file.setTopLeft(p_w_file_final);
    animation5->setKeyValueAt(1,rect_file);
    animation5->setEasingCurve(QEasingCurve::InOutQuad);

    parralle_anim = new QParallelAnimationGroup;
    parralle_anim->addAnimation(animation1);
    parralle_anim->addAnimation(animation2);
    parralle_anim->addAnimation(animation3);
    parralle_anim->addAnimation(animation4);
    parralle_anim->addAnimation(animation5);

    parralle_anim->start(QParallelAnimationGroup::DeleteWhenStopped);

    state = 0;
}

void c_entry_point::slot_open_animation_finished() {
    emit load_builder_from(format,path_json,id);
}
