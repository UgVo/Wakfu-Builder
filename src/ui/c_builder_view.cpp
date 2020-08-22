#include "c_builder_view.h"
#include "ui_c_builder_view.h"

#include "../mainwindow.h"

c_builder_view::c_builder_view(c_dbmanager *_manager,  QCompleter* search_completer, QWidget *_parent) :
    QWidget(_parent),
    ui(new Ui::c_builder_view)
{
    ui->setupUi(this);
    manager = _manager;
    build = new c_build;
    id = 0;
    parent = static_cast<MainWindow*>(_parent);

    //UI
    result_display = new c_result_display(manager,this);
    status_build = new c_status_build(this);
    element_display = new c_elements_display(this);
    build_display = new c_build_display(build,this);
    //build_display->set_item_viewers();
    search_widget = new c_search_widget(manager,search_completer,this);
    aptitude_display = new c_aptitudes_display(this);
    tc_resume = new c_theory_craft_resume(this);
    enchantement_display = new c_enchantement_display(this,manager,build);

    ui->build_layout->insertWidget(0,status_build);
    ui->build_layout->insertWidget(1,build_display);
    ui->build_layout->insertWidget(2,element_display);

    ui->horizontalLayout_2->insertWidget(0,result_display);
    ui->horizontalLayout_2->setAlignment(result_display,Qt::AlignTop);
    ui->verticalLayout->insertWidget(0,search_widget);
    ui->verticalLayout->setAlignment(search_widget,Qt::AlignTop);
    ui->verticalLayout->insertWidget(2,tc_resume);
    ui->verticalLayout->setAlignment(tc_resume,Qt::AlignTop);

    status_build->setDisabled(true);
    build_display->setDisabled(true);
    element_display->setDisabled(true);
    result_display->setDisabled(true);
    search_widget->setDisabled(true);
    ui->tabWidget->setDisabled(true);

    QObject::connect(search_widget,&c_search_widget::new_search_result,result_display,&c_result_display::slot_new_search_result);
    QObject::connect(search_widget,&c_search_widget::new_search_result_sorted,result_display,&c_result_display::slot_new_search_result_sorted);
    QObject::connect(result_display,&c_result_display::item_doubleCliked,build_display,&c_build_display::equip_new_item);
    QObject::connect(status_build,&c_status_build::lvl_changed,search_widget,&c_search_widget::setLvl);
    QObject::connect(status_build,&c_status_build::lvl_changed,build,&c_build::setLvl);
    QObject::connect(status_build,&c_status_build::lvl_changed,aptitude_display,&c_aptitudes_display::setLvl);
    QObject::connect(status_build,&c_status_build::lvl_changed,enchantement_display,&c_enchantement_display::slot_setLevel);
    QObject::connect(status_build,&c_status_build::bonus_changed,build,&c_build::slot_bonus_changed);
    QObject::connect(element_display,&c_elements_display::newElements,build,&c_build::setElements);
    QObject::connect(build_display,&c_build_display::load_search_position,search_widget,&c_search_widget::slot_load_search_position);
    QObject::connect(aptitude_display,&c_aptitudes_display::value_changed,build,&c_build::slot_aptitude_value_changed);
    QObject::connect(result_display,&c_result_display::item_hovered,build_display,&c_build_display::slot_item_hovered);
    QObject::connect(result_display,&c_result_display::item_hide,build_display,&c_build_display::slot_item_hide);

    ui->widget->setStyleSheet(QString("QWidget#widget{background-color:%1}").arg(app_color::grey_blue));
    status_build->setLvl(200);
    QObject::connect(status_build,&c_status_build::show_class_popup,this,&c_builder_view::slot_show_class_popup);

    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(ui->tabWidget);
    shadow->setColor(QColor(91, 108, 142, 180));
    shadow->setOffset(2,2);
    ui->tabWidget->setGraphicsEffect(shadow);

    shadow = new QGraphicsDropShadowEffect(enchantement_display);
    shadow->setColor(QColor(91, 108, 142, 180));
    shadow->setOffset(2,2);
    enchantement_display->setGraphicsEffect(shadow);
    //ui->tabWidget->setStyleSheet(QString("QTabWidget::pane {border: 0px solid black; border-radius: 3px; background: %1;} QTabWidget::tab-bar:top {top: 1px;}QTabWidget::tab-bar:bottom {bottom: 1px;}QTabWidget::tab-bar:left {right: 1px;}QTabWidget::tab-bar:right {left: 1px;}QTabBar::tab {border: 1px solid black;}QTabBar::tab:selected {background: white;}QTabBar::tab:!selected {background: silver;}QTabBar::tab:!selected:hover {background: #999;}QTabBar::tab:top:!selected {margin-top: 3px;}QTabBar::tab:bottom:!selected {margin-bottom: 3px;}QTabBar::tab:top, QTabBar::tab:bottom {min-width: 8ex;margin-right: -1px;padding: 5px 10px 5px 10px;}QTabBar::tab:top:selected {border-bottom-color: none;}QTabBar::tab:bottom:selected {border-top-color: none;}QTabBar::tab:top:last, QTabBar::tab:bottom:last,QTabBar::tab:top:only-one, QTabBar::tab:bottom:only-one {margin-right: 0;}QTabBar::tab:left:!selected {margin-right: 3px;}QTabBar::tab:right:!selected {margin-left: 3px;}QTabBar::tab:left, QTabBar::tab:right {min-height: 8ex;margin-bottom: -1px;padding: 10px 5px 10px 5px;}QTabBar::tab:left:selected {border-left-color: none;}QTabBar::tab:right:selected {border-right-color: none;}QTabBar::tab:left:last, QTabBar::tab:right:last,QTabBar::tab:left:only-one, QTabBar::tab:right:only-one {margin-bottom: 0;}").arg(app_color::gery_blue_2));
    ui->tabWidget->setStyleSheet(QString("QTabWidget#tabWidget::pane {border: 0px solid black; border-radius: 3px; border-bottom-left-radius: 0px; background: %1;} "
                                         "#tabWidget > QTabBar::tab {border: 0px solid black; border-bottom-right-radius: 3px; border-bottom-left-radius: 3px; background: %1; margin-right: 10px; width: 150px; padding-right:-55px; padding-left:55px;} "
                                         "#tabWidget > QTabBar::tab:!selected {background: %2;}").arg(app_color::grey_blue_2).arg(app_color::grey_blue_3));
    ui->tabWidget->setTabIcon(0,QIcon(":/images/divers/equipments.png"));
    ui->tabWidget->setTabIcon(1,QIcon(":/images/divers/aptitude.png"));
    ui->tabWidget->setTabIcon(2,QIcon(":/images/divers/spell.png"));
    ui->tabWidget->setTabIcon(3,QIcon(":/images/divers/enchantement.png"));

    ui->horizontalLayout_5->addWidget(aptitude_display);
    ui->verticalLayout_3->addWidget(enchantement_display);
    this->setWindowState(Qt::WindowMaximized);

    state_column_number = -1;
    state_element = 0;

    element_popup = nullptr;

    calcul = new c_calcul;
    calcul->setBuild(build);
    calcul->setTc_resume(tc_resume);
    QObject::connect(build,&c_build::updated,calcul,&c_calcul::computeMainMastery);

    QObject::connect(element_display,&c_elements_display::doubleCliked,this,&c_builder_view::slot_show_element_popup);

    class_selection_popup = nullptr;

}

c_builder_view::~c_builder_view()
{
    delete ui;
}

c_status_build *c_builder_view::getStatus_build() const {
    return status_build;
}

c_build_display *c_builder_view::getBuild_display() const {
    return build_display;
}

c_elements_display *c_builder_view::getElement_display() const {
    return element_display;
}

int c_builder_view::getId() const {
    return id;
}

void c_builder_view::setId(int value) {
    id = value;
}

QString c_builder_view::getPath() const
{
    return path;
}

void c_builder_view::setPath(const QString &value)
{
    path = value;
}

MainWindow *c_builder_view::getParent() const {
    return parent;
}

void c_builder_view::resizeEvent(QResizeEvent *event) {
    if (( this->rect().width() < 1780 && state_column_number == -1) ||  (this->rect().width() < 1780 && state_column_number==3) ) {
        result_display->setMinimumSize(506,755);
        result_display->setMaximumSize(506,755);
        result_display->refreshView();
        state_column_number = 2;
    } else if ((this->rect().width() >= 1780 && state_column_number == -1) ||  (this->rect().width() >= 1780 && state_column_number==2)) {
        result_display->setMinimumSize(762,755);
        result_display->setMaximumSize(762,755);
        result_display->refreshView();
        state_column_number = 3;
    }
    if (state_element == 0) {
        if (element_popup != nullptr) {
            QPoint elem_popup_pos = QPoint((rect().width()-element_popup->width())/2,-element_popup->height());
            element_popup->move(elem_popup_pos);
        }
        if (id != 0) {
            status_build->setDisabled(false);
            build_display->setDisabled(false);
            element_display->setDisabled(false);
            result_display->setDisabled(false);
            search_widget->setDisabled(false);
            ui->tabWidget->setDisabled(false);
            timer.stop();
        } else if (timer.remainingTime()==-1) {
            timer.start(2000);
            QObject::connect(&timer,&QTimer::timeout,this,&c_builder_view::slot_show_element_popup);
        }
    } else if (state_element == 1) {
        if (element_popup != nullptr) {
            QPoint elem_popup_pos = QPoint((rect().width()-element_popup->width())/2,(rect().height() - element_popup->height())/3);
            element_popup->move(elem_popup_pos);
        }
    }

c_enchantement_display *c_builder_view::getEnchantement_display() const
{
    return enchantement_display;
}

c_aptitudes_display *c_builder_view::getAptitude_display() const
{
    return aptitude_display;
}

void c_builder_view::slot_save(c_io_manager::jsonformat format, QString path) {
    c_io_manager io_manager(manager);
    io_manager.save(this,format,path);
}

bool c_builder_view::slot_load(c_io_manager::jsonformat format, QString path) {
    c_io_manager io_manager(manager);
    return io_manager.load(this,format,path);
}

bool c_builder_view::slot_loadFrom(c_io_manager::jsonformat format, QString path_json,int id) {
    c_io_manager io_manager(manager)    ;
    return io_manager.loadFrom(this,format,path_json,id);
}

void c_builder_view::slot_update(c_io_manager::jsonformat format) {
    c_io_manager io_manager(manager);
    io_manager.update(this,format,path);
}

void c_builder_view::slot_show_element_popup() {
    if (element_popup != nullptr) {
        QObject::disconnect(element_popup,&c_element_popup_widget::accepted,this,&c_builder_view::slot_hide_element_popup);
        element_popup->deleteLater();
        element_popup = nullptr;
    }
    element_popup = new c_element_popup_widget(this);
    element_popup->show();
    QObject::connect(element_popup,&c_element_popup_widget::accepted,this,&c_builder_view::slot_hide_element_popup);
    status_build->setDisabled(true);
    build_display->setDisabled(true);
    element_display->setDisabled(true);
    result_display->setDisabled(true);
    search_widget->setDisabled(true);
    ui->tabWidget->setDisabled(true);
    timer.stop();
    QPoint elem_popup_pos = QPoint((rect().width()-element_popup->width())/2,-element_popup->height());
    QPoint elem_popup_pos_final = QPoint((rect().width()-element_popup->width())/2,(rect().height() - element_popup->height())/3);
    animation1 = new QPropertyAnimation(element_popup,"geometry");
    animation1->setDuration(1000);
    QRect rect_button_new = element_popup->rect();
    rect_button_new.setTopLeft(elem_popup_pos);
    animation1->setKeyValueAt(0,rect_button_new);
    rect_button_new.setTopLeft(elem_popup_pos_final);
    animation1->setKeyValueAt(1,rect_button_new);
    animation1->setEasingCurve(QEasingCurve::OutCubic);
    animation1->start(QPropertyAnimation::DeleteWhenStopped);
}

void c_builder_view::slot_hide_element_popup() {
    state_element = 2;
    QPoint elem_popup_pos_final = QPoint((rect().width()-element_popup->width())/2,-element_popup->height());
    QPoint elem_popup_pos = QPoint((rect().width()-element_popup->width())/2,(rect().height() - element_popup->height())/3);
    animation1 = new QPropertyAnimation(element_popup,"geometry");
    animation1->setDuration(1000);
    QRect rect_button_new = element_popup->rect();
    rect_button_new.setTopLeft(elem_popup_pos);
    animation1->setKeyValueAt(0,rect_button_new);
    rect_button_new.setTopLeft(elem_popup_pos_final);
    animation1->setKeyValueAt(1,rect_button_new);
    animation1->setEasingCurve(QEasingCurve::InCubic);
    animation1->start(QPropertyAnimation::DeleteWhenStopped);

    status_build->setDisabled(false);
    build_display->setDisabled(false);
    element_display->setDisabled(false);
    result_display->setDisabled(false);
    search_widget->setDisabled(false);
    ui->tabWidget->setDisabled(false);

    element_display->setElements(element_popup->getElems());
}

void c_builder_view::slot_show_class_popup() {
    if (class_selection_popup != nullptr) {
        QObject::disconnect(class_selection_popup,&c_class_selection::class_chosen,this,&c_builder_view::slot_hide_class_popup);
        class_selection_popup->deleteLater();
        class_selection_popup = nullptr;
    }
    class_selection_popup = new c_class_selection(this);
    class_selection_popup->show();
    QObject::connect(class_selection_popup,&c_class_selection::class_chosen,status_build,&c_status_build::slot_class_changed);
    QObject::connect(class_selection_popup,&c_class_selection::class_chosen,this,&c_builder_view::slot_hide_class_popup);
    QObject::connect(class_selection_popup,&c_class_selection::rejected,this,&c_builder_view::slot_hide_class_popup);
    status_build->setDisabled(true);
    build_display->setDisabled(true);
    element_display->setDisabled(true);
    result_display->setDisabled(true);
    search_widget->setDisabled(true);
    ui->tabWidget->setDisabled(true);
    QPoint class_popup_pos = QPoint((rect().width()-class_selection_popup->width())/2,-class_selection_popup->height());
    QPoint class_popup_pos_final = QPoint((rect().width()-class_selection_popup->width())/2,(rect().height() - class_selection_popup->height())/3);
    animation1 = new QPropertyAnimation(class_selection_popup,"geometry");
    animation1->setDuration(1000);
    QRect rect_button_new = class_selection_popup->rect();
    rect_button_new.setTopLeft(class_popup_pos);
    animation1->setKeyValueAt(0,rect_button_new);
    rect_button_new.setTopLeft(class_popup_pos_final);
    animation1->setKeyValueAt(1,rect_button_new);
    animation1->setEasingCurve(QEasingCurve::OutCubic);
    animation1->start(QPropertyAnimation::DeleteWhenStopped);
}

void c_builder_view::slot_hide_class_popup() {
    QPoint class_popup_pos_final = QPoint((rect().width()-class_selection_popup->width())/2,-class_selection_popup->height());
    QPoint class_popup_pos = QPoint((rect().width()-class_selection_popup->width())/2,(rect().height() - class_selection_popup->height())/3);
    animation1 = new QPropertyAnimation(class_selection_popup,"geometry");
    animation1->setDuration(1000);
    QRect rect_button_new = class_selection_popup->rect();
    rect_button_new.setTopLeft(class_popup_pos);
    animation1->setKeyValueAt(0,rect_button_new);
    rect_button_new.setTopLeft(class_popup_pos_final);
    animation1->setKeyValueAt(1,rect_button_new);
    animation1->setEasingCurve(QEasingCurve::InCubic);
    animation1->start(QPropertyAnimation::DeleteWhenStopped);

    status_build->setDisabled(false);
    build_display->setDisabled(false);
    element_display->setDisabled(false);
    result_display->setDisabled(false);
    search_widget->setDisabled(false);
    ui->tabWidget->setDisabled(false);
}
