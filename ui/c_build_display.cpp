#include "c_build_display.h"
#include "ui_c_build_display.h"

c_build_display::c_build_display(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::c_build_display) {
    ui->setupUi(this);
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(ui->widget_vie);
    shadow->setColor(QColor(91, 108, 142, 180));
    shadow->setOffset(2,2);
    ui->widget_vie->setGraphicsEffect(static_cast<QGraphicsEffect*>(shadow));
    shadow = new QGraphicsDropShadowEffect(ui->widget_cc);
    shadow->setColor(QColor(91, 108, 142, 180));
    shadow->setOffset(2,2);
    ui->widget_cc->setGraphicsEffect(static_cast<QGraphicsEffect*>(shadow));
    shadow = new QGraphicsDropShadowEffect(ui->widget_armure);
    shadow->setColor(QColor(91, 108, 142, 180));
    shadow->setOffset(2,2);
    ui->widget_armure->setGraphicsEffect(static_cast<QGraphicsEffect*>(shadow));
    shadow = new QGraphicsDropShadowEffect(ui->widget_pa);
    shadow->setColor(QColor(91, 108, 142, 180));
    shadow->setOffset(2,2);
    ui->widget_pa->setGraphicsEffect(static_cast<QGraphicsEffect*>(shadow));
    shadow = new QGraphicsDropShadowEffect(ui->widget_pm);
    shadow->setColor(QColor(91, 108, 142, 180));
    shadow->setOffset(2,2);
    ui->widget_pm->setGraphicsEffect(static_cast<QGraphicsEffect*>(shadow));
    shadow = new QGraphicsDropShadowEffect(ui->widget_pw);
    shadow->setColor(QColor(91, 108, 142, 180));
    shadow->setOffset(2,2);
    ui->widget_pw->setGraphicsEffect(static_cast<QGraphicsEffect*>(shadow));
    shadow = new QGraphicsDropShadowEffect(ui->widget_air);
    shadow->setColor(QColor(91, 108, 142, 180));
    shadow->setOffset(2,2);
    ui->widget_air->setGraphicsEffect(static_cast<QGraphicsEffect*>(shadow));
    shadow = new QGraphicsDropShadowEffect(ui->widget_ini);
    shadow->setColor(QColor(91, 108, 142, 180));
    shadow->setOffset(2,2);
    ui->widget_ini->setGraphicsEffect(static_cast<QGraphicsEffect*>(shadow));
    shadow = new QGraphicsDropShadowEffect(ui->widget_m_cc);
    shadow->setColor(QColor(91, 108, 142, 180));
    shadow->setOffset(2,2);
    ui->widget_m_cc->setGraphicsEffect(static_cast<QGraphicsEffect*>(shadow));
    shadow = new QGraphicsDropShadowEffect(ui->widget_mono);
    shadow->setColor(QColor(91, 108, 142, 180));
    shadow->setOffset(2,2);
    ui->widget_mono->setGraphicsEffect(static_cast<QGraphicsEffect*>(shadow));
    shadow = new QGraphicsDropShadowEffect(ui->widget_r_cc);
    shadow->setColor(QColor(91, 108, 142, 180));
    shadow->setOffset(2,2);
    ui->widget_r_cc->setGraphicsEffect(static_cast<QGraphicsEffect*>(shadow));
    shadow = new QGraphicsDropShadowEffect(ui->widget_soin);
    shadow->setColor(QColor(91, 108, 142, 180));
    shadow->setOffset(2,2);
    ui->widget_soin->setGraphicsEffect(static_cast<QGraphicsEffect*>(shadow));
    shadow = new QGraphicsDropShadowEffect(ui->widget_zone);
    shadow->setColor(QColor(91, 108, 142, 180));
    shadow->setOffset(2,2);
    ui->widget_zone->setGraphicsEffect(static_cast<QGraphicsEffect*>(shadow));
    shadow = new QGraphicsDropShadowEffect(ui->widget_feu);
    shadow->setColor(QColor(91, 108, 142, 180));
    shadow->setOffset(2,2);
    ui->widget_feu->setGraphicsEffect(static_cast<QGraphicsEffect*>(shadow));
    shadow = new QGraphicsDropShadowEffect(ui->widget_barda);
    shadow->setColor(QColor(91, 108, 142, 180));
    shadow->setOffset(2,2);
    ui->widget_barda->setGraphicsEffect(static_cast<QGraphicsEffect*>(shadow));
    shadow = new QGraphicsDropShadowEffect(ui->widget_eau);
    shadow->setColor(QColor(91, 108, 142, 180));
    shadow->setOffset(2,2);
    ui->widget_eau->setGraphicsEffect(static_cast<QGraphicsEffect*>(shadow));
    shadow = new QGraphicsDropShadowEffect(ui->widget_terre);
    shadow->setColor(QColor(91, 108, 142, 180));
    shadow->setOffset(2,2);
    ui->widget_terre->setGraphicsEffect(static_cast<QGraphicsEffect*>(shadow));
    shadow = new QGraphicsDropShadowEffect(ui->widget_m_dos);
    shadow->setColor(QColor(91, 108, 142, 180));
    shadow->setOffset(2,2);
    ui->widget_m_dos->setGraphicsEffect(static_cast<QGraphicsEffect*>(shadow));
    shadow = new QGraphicsDropShadowEffect(ui->widget_melee);
    shadow->setColor(QColor(91, 108, 142, 180));
    shadow->setOffset(2,2);
    ui->widget_melee->setGraphicsEffect(static_cast<QGraphicsEffect*>(shadow));
    shadow = new QGraphicsDropShadowEffect(ui->widget_porte);
    shadow->setColor(QColor(91, 108, 142, 180));
    shadow->setOffset(2,2);
    ui->widget_porte->setGraphicsEffect(static_cast<QGraphicsEffect*>(shadow));
    shadow = new QGraphicsDropShadowEffect(ui->widget_r_dos);
    shadow->setColor(QColor(91, 108, 142, 180));
    shadow->setOffset(2,2);
    ui->widget_r_dos->setGraphicsEffect(static_cast<QGraphicsEffect*>(shadow));
    shadow = new QGraphicsDropShadowEffect(ui->widget_tacle);
    shadow->setColor(QColor(91, 108, 142, 180));
    shadow->setOffset(2,2);
    ui->widget_tacle->setGraphicsEffect(static_cast<QGraphicsEffect*>(shadow));
    shadow = new QGraphicsDropShadowEffect(ui->widget_m_soin);
    shadow->setColor(QColor(91, 108, 142, 180));
    shadow->setOffset(2,2);
    ui->widget_m_soin->setGraphicsEffect(static_cast<QGraphicsEffect*>(shadow));
    shadow = new QGraphicsDropShadowEffect(ui->widget_parade);
    shadow->setColor(QColor(91, 108, 142, 180));
    shadow->setOffset(2,2);
    ui->widget_parade->setGraphicsEffect(static_cast<QGraphicsEffect*>(shadow));
    shadow = new QGraphicsDropShadowEffect(ui->widget_berserk);
    shadow->setColor(QColor(91, 108, 142, 180));
    shadow->setOffset(2,2);
    ui->widget_berserk->setGraphicsEffect(static_cast<QGraphicsEffect*>(shadow));
    shadow = new QGraphicsDropShadowEffect(ui->widget_dommage);
    shadow->setColor(QColor(91, 108, 142, 180));
    shadow->setOffset(2,2);
    ui->widget_dommage->setGraphicsEffect(static_cast<QGraphicsEffect*>(shadow));
    shadow = new QGraphicsDropShadowEffect(ui->widget_esquive);
    shadow->setColor(QColor(91, 108, 142, 180));
    shadow->setOffset(2,2);
    ui->widget_esquive->setGraphicsEffect(static_cast<QGraphicsEffect*>(shadow));
    shadow = new QGraphicsDropShadowEffect(ui->widget_sagesse);
    shadow->setColor(QColor(91, 108, 142, 180));
    shadow->setOffset(2,2);
    ui->widget_sagesse->setGraphicsEffect(static_cast<QGraphicsEffect*>(shadow));
    shadow = new QGraphicsDropShadowEffect(ui->widget_volonte);
    shadow->setColor(QColor(91, 108, 142, 180));
    shadow->setOffset(2,2);
    ui->widget_volonte->setGraphicsEffect(static_cast<QGraphicsEffect*>(shadow));
    shadow = new QGraphicsDropShadowEffect(ui->widget_controle);
    shadow->setColor(QColor(91, 108, 142, 180));
    shadow->setOffset(2,2);
    ui->widget_controle->setGraphicsEffect(static_cast<QGraphicsEffect*>(shadow));
    shadow = new QGraphicsDropShadowEffect(ui->widget_distance);
    shadow->setColor(QColor(91, 108, 142, 180));
    shadow->setOffset(2,2);
    ui->widget_distance->setGraphicsEffect(static_cast<QGraphicsEffect*>(shadow));
    shadow = new QGraphicsDropShadowEffect(ui->widget_prospection);
    shadow->setColor(QColor(91, 108, 142, 180));
    shadow->setOffset(2,2);
    ui->widget_prospection->setGraphicsEffect(static_cast<QGraphicsEffect*>(shadow));
    setStyleSheet("c_build_display {background-color: #6A8BA8;} .QWidget.QWidget{background-color: #305A7F; border: 1px solid #305A7F; border-radius: 4px;} .QSpinBox{background-color: #305A7F;color:white; } .QLabel{color:white}");
    QVBoxLayout* equipementLayout = static_cast<QVBoxLayout*>(ui->equipement_frame->layout());
    foreach (QString position, c_item::position()) {
        item_position_map[position] = new c_item_viewer(position,this);
        item_position_map[position]->setStyleSheet(".QWidget{background-color: #6A8BA8; border: 1px solid #6A8BA8;}");
        connect(item_position_map[position],&c_item_viewer::unequip,&_build,&c_build::unequip);
        equipementLayout->insertWidget(item_position_map.size(),item_position_map[position]);
    }
    connect(&_build,&c_build::updated,this,&c_build_display::update_view);
    connect(&_build,&c_build::disableSecondWeapon,this,&c_build_display::slot_second_hand_disabled);

}

c_build_display::~c_build_display() {
    delete ui;
}

c_build c_build_display::build() const {
    return _build;
}

void c_build_display::setBuild(const c_build &build) {
    _build = build;
    update_view();
}

void c_build_display::update_view() {
    QMap<QString,int> bonuses = _build.getBonuses();
    ui->sp_pv->setValue(bonuses["Vie"]);
    ui->sp_pa->setValue(bonuses["PA"]);
    ui->sp_pm->setValue(bonuses["PM"]);
    ui->sp_pw->setValue(bonuses["PW"]);
    ui->sp_d_feu->setValue(bonuses["Maîtrise Élémentaire Feu"]);
    ui->sp_d_eau->setValue(bonuses["Maîtrise Élémentaire Eau"]);
    ui->sp_d_terre->setValue(bonuses["Maîtrise Élémentaire Terre"]);
    ui->sp_d_air->setValue(bonuses["Maîtrise Élémentaire Air"]);
    ui->sp_r_feu->setValue(bonuses["Résistance Feu"]);
    ui->sp_r_eau->setValue(bonuses["Résistance Eau"]);
    ui->sp_r_terre->setValue(bonuses["Résistance Terre"]);
    ui->sp_r_air->setValue(bonuses["Résistance Air"]);
    ui->sp_dommage->setValue(bonuses["Dommages infligés"]);
    ui->sp_soin->setValue(bonuses["Soins réalisés"]);
    ui->sp_parade->setValue(bonuses["Parade"]);
    ui->sp_cc->setValue(bonuses["Coup Critique"]);
    ui->sp_ini->setValue(bonuses["Initiative"]);
    ui->sp_porte->setValue(bonuses["Portée"]);
    ui->sp_esquive->setValue(bonuses["Esquive"]);
    ui->sp_tacle->setValue(bonuses["Tacle"]);
    ui->sp_sagesse->setValue(bonuses["Sagesse"]);
    ui->sp_prospec->setValue(bonuses["Prospection"]);
    ui->sp_controle->setValue(bonuses["Contrôle"]);
    ui->sp_barda->setValue(bonuses["Art du barda"]);
    ui->sp_volonte->setValue(bonuses["Volonté"]);
    ui->sp_m_cc->setValue(bonuses["Maîtrise Critique"]);
    ui->sp_r_cc->setValue(bonuses["Résistance Critique"]);
    ui->sp_m_dos->setValue(bonuses["Maîtrise Dos"]);
    ui->sp_r_dos->setValue(bonuses["Résistance Dos"]);
    ui->sp_melee->setValue(bonuses["Maîtrise Mêlée"]);
    ui->sp_distance->setValue(bonuses["Maîtrise Distance"]);
    ui->sp_mono->setValue(bonuses["Maîtrise Monocible"]);
    ui->sp_zone->setValue(bonuses["Maîtrise Zone"]);
    ui->sp_m_soin->setValue(bonuses["Maîtrise Soin"]);
    ui->sp_berserk->setValue(bonuses["Maîtrise Berserk"]);

    ui->sp_r_air_100->setValue(calcul.compute_reduction(bonuses["Résistance Air"]));
    ui->sp_r_feu_100->setValue(calcul.compute_reduction(bonuses["Résistance Feu"]));
    ui->sp_r_eau_100->setValue(calcul.compute_reduction(bonuses["Résistance Eau"]));
    ui->sp_r_terre_100->setValue(calcul.compute_reduction(bonuses["Résistance Terre"]));
    QMap<QString,c_item*> equipement = _build.getEquipment_pt();
    equipement.remove("");

    foreach (QString position, equipement.keys()) {
        item_position_map[position]->setItem(equipement[position]);
    }
}

void c_build_display::equip_new_item(c_item item) {
    _build.equip(item);
}

void c_build_display::slot_second_hand_disabled(bool state) {
    qDebug() << "slot_second_hand_disabled";
    if (state) {
        item_position_map["SECOND_WEAPON"]->disable(item_position_map["FIRST_WEAPON"]->get_item()->getGfxId());
    } else {
        item_position_map["SECOND_WEAPON"]->enable();
    }

}
