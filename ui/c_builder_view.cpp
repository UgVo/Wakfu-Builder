#include "c_builder_view.h"
#include "ui_c_builder_view.h"

c_builder_view::c_builder_view(c_dbmanager *_manager, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::c_builder_view)
{
    ui->setupUi(this);
    manager = _manager;
    build = new c_build;
    id = 0;

    //UI
    result_display = new c_result_display(manager);
    status_build = new c_status_build;
    element_display = new c_elements_display;
    build_display = new c_build_display(build);
    //build_display->set_item_viewers();
    search_widget = new c_search_widget(manager);

    ui->build_layout->insertWidget(0,status_build);
    ui->build_layout->insertWidget(1,build_display);
    ui->build_layout->insertWidget(2,element_display);

    ui->horizontalLayout->insertWidget(2,result_display);
    ui->horizontalLayout->setAlignment(result_display,Qt::AlignTop);
    ui->horizontalLayout->insertWidget(3,search_widget);
    ui->horizontalLayout->setAlignment(search_widget,Qt::AlignTop);

    QObject::connect(search_widget,&c_search_widget::new_search_result,result_display,&c_result_display::slot_new_search_result);
    QObject::connect(search_widget,&c_search_widget::new_search_result_sorted,result_display,&c_result_display::slot_new_search_result_sorted);
    QObject::connect(result_display,&c_result_display::item_doubleCliked,build_display,&c_build_display::equip_new_item);
    QObject::connect(status_build,&c_status_build::lvl_changed,search_widget,&c_search_widget::setLvl);
    QObject::connect(status_build,&c_status_build::lvl_changed,build,&c_build::setLvl);
    QObject::connect(status_build,&c_status_build::bonus_changed,build,&c_build::slot_bonus_changed);
    QObject::connect(element_display,&c_elements_display::newElements,build,&c_build::setElements);
    QObject::connect(build_display,&c_build_display::load_search_position,search_widget,&c_search_widget::slot_load_search_position);

    ui->widget->setStyleSheet(QString("QWidget#widget{background-color:%1}").arg(app_color::grey_blue));
    status_build->setLvl(200);

    this->setWindowState(Qt::WindowMaximized);
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

void c_builder_view::slot_save(c_io_manager::jsonformat format, QString path) {
    c_io_manager io_manager(manager);
    io_manager.save(this,format,path);
}

bool c_builder_view::slot_load(c_io_manager::jsonformat format, QString path) {
    c_io_manager io_manager(manager);
    return io_manager.load(this,format,path);
}

void c_builder_view::slot_update(c_io_manager::jsonformat format) {
    c_io_manager io_manager(manager);
    io_manager.update(this,format,path);
}
