#include "c_aptitudes_display.h"
#include "ui_c_aptitudes_display.h"

#include "c_builder_view.h"
#include "../mainwindow.h"

c_aptitudes_display::c_aptitudes_display(QWidget *_parent) :
    QWidget(_parent),
    ui(new Ui::c_aptitudes_display)
{

    parent = static_cast<c_builder_view*>(_parent);
    ui->setupUi(this);

    this->setStyleSheet(QString("color : white; "));
    ui->icon_intell->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    ui->icon_intell->setScaledContents(true);
    QFont font = ui->label_intell->font();
    font.setFamily("Wakfu Client Interface Verdana");
    font.setPointSize(15);
    ui->label_intell->setFont(font);
    ui->label_agil->setFont(font);
    ui->label_force->setFont(font);
    ui->label_chance->setFont(font);
    ui->label_majeur->setFont(font);
    ui->icon_agil->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    ui->icon_agil->setScaledContents(true);
    ui->icon_force->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    ui->icon_force->setScaledContents(true);
    ui->icon_chance->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    ui->icon_chance->setScaledContents(true);
    ui->icon_majeur->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    ui->icon_majeur->setScaledContents(true);

    map_counts_labels["intelligence"] = ui->intell_count;
    map_counts_labels["force"] = ui->force_count;
    map_counts_labels["agilite"] = ui->agil_count;
    map_counts_labels["chance"] = ui->chance_count;
    map_counts_labels["majeur"] = ui->majeur_count;

    ui->intell_count->setStyleSheet(QString("background-color: %1; border: 1px solid white; border-radius: 8px; color:white; padding: 2px ").arg(app_color::dark));
    ui->chance_count->setStyleSheet(QString("background-color: %1; border: 1px solid white; border-radius: 8px; color:white; padding: 2px ").arg(app_color::dark));
    ui->agil_count->setStyleSheet(QString("background-color: %1; border: 1px solid white; border-radius: 8px; color:white; padding: 2px ").arg(app_color::dark));
    ui->force_count->setStyleSheet(QString("background-color: %1; border: 1px solid white; border-radius: 8px; color:white; padding: 2px ").arg(app_color::dark));
    ui->majeur_count->setStyleSheet(QString("background-color: %1; border: 1px solid white; border-radius: 8px; color:white; padding: 2px ").arg(app_color::dark));

    ui->widget_agil->setStyleSheet(QString("background-color: %1; border-radius: 3px; ").arg(app_color::dark_blue));
    ui->widget_force->setStyleSheet(QString("background-color: %1; border-radius: 3px; ").arg(app_color::dark_blue));
    ui->widget_chance->setStyleSheet(QString("background-color: %1; border-radius: 3px; ").arg(app_color::dark_blue));
    ui->widget_intell->setStyleSheet(QString("background-color: %1; border-radius: 3px; ").arg(app_color::dark_blue));
    ui->widget_majeur->setStyleSheet(QString("background-color: %1; border-radius: 3px; ").arg(app_color::dark_blue));

    map_unites["intelligence"] = new QList<c_aptitude_unite*>;
    map_unites["intelligence"]->push_back(new c_aptitude_unite("% Point de Vie",-1,"big_vie_100","intelligence",this));
    ui->layout_intell->insertWidget(1,map_unites["intelligence"]->last());
    map_unites["intelligence"]->push_back(new c_aptitude_unite("Résistance Élémentaire",10,"big_resistance","intelligence",this));
    ui->layout_intell->insertWidget(2,map_unites["intelligence"]->last());
    map_unites["intelligence"]->push_back(new c_aptitude_unite("Barrière",10,"big_barriere","intelligence",this));
    ui->layout_intell->insertWidget(3,map_unites["intelligence"]->last());
    map_unites["intelligence"]->push_back(new c_aptitude_unite("% Soin Reçu",5,"big_soin","intelligence",this));
    ui->layout_intell->insertWidget(4,map_unites["intelligence"]->last());
    map_unites["intelligence"]->push_back(new c_aptitude_unite("% Point de Vie en Armure",10,"big_armure","intelligence",this));
    ui->layout_intell->insertWidget(5,map_unites["intelligence"]->last());

    map_unites["force"] = new QList<c_aptitude_unite*>;
    map_unites["force"]->push_back(new c_aptitude_unite("Maitrise Élémentaire",-1,"big_elementaire","force",this));
    ui->layout_force->insertWidget(1,map_unites["force"]->last());
    map_unites["force"]->push_back(new c_aptitude_unite("Maitrise Monocible",20,"big_monocible","force",this));
    ui->layout_force->insertWidget(2,map_unites["force"]->last());
    map_unites["force"]->push_back(new c_aptitude_unite("Maitrise Zone",20,"big_zone","force",this));
    ui->layout_force->insertWidget(3,map_unites["force"]->last());
    map_unites["force"]->push_back(new c_aptitude_unite("Maitrise Mêlée",20,"big_melee","force",this));
    ui->layout_force->insertWidget(4,map_unites["force"]->last());
    map_unites["force"]->push_back(new c_aptitude_unite("Maitrise Distance",20,"big_distance","force",this));
    ui->layout_force->insertWidget(5,map_unites["force"]->last());
    map_unites["force"]->push_back(new c_aptitude_unite("Point de Vie",-1,"big_point_vie","force",this));
    ui->layout_force->insertWidget(6,map_unites["force"]->last());

    map_unites["agilite"] = new QList<c_aptitude_unite*>;
    map_unites["agilite"]->push_back(new c_aptitude_unite("Tacle",-1,"big_tacle","agilite",this));
    ui->layout_agil->insertWidget(1,map_unites["agilite"]->last());
    map_unites["agilite"]->push_back(new c_aptitude_unite("Esquive",-1,"big_esquive","agilite",this));
    ui->layout_agil->insertWidget(2,map_unites["agilite"]->last());
    map_unites["agilite"]->push_back(new c_aptitude_unite("Initiative",20,"big_initiative","agilite",this));
    ui->layout_agil->insertWidget(3,map_unites["agilite"]->last());
    map_unites["agilite"]->push_back(new c_aptitude_unite("Tacle et Esquive",-1,"big_tacle_esquive","agilite",this));
    ui->layout_agil->insertWidget(4,map_unites["agilite"]->last());
    map_unites["agilite"]->push_back(new c_aptitude_unite("Volonté",20,"big_volonte","agilite",this));
    ui->layout_agil->insertWidget(5,map_unites["agilite"]->last());

    map_unites["chance"] = new QList<c_aptitude_unite*>;
    map_unites["chance"]->push_back(new c_aptitude_unite("% Coup Critique",20,"big_critique","chance",this));
    ui->layout_chance->insertWidget(1,map_unites["chance"]->last());
    map_unites["chance"]->push_back(new c_aptitude_unite("% Parade",20,"big_parade","chance",this));
    ui->layout_chance->insertWidget(2,map_unites["chance"]->last());
    map_unites["chance"]->push_back(new c_aptitude_unite("Maîtrise Critique",-1,"big_critique_m","chance",this));
    ui->layout_chance->insertWidget(3,map_unites["chance"]->last());
    map_unites["chance"]->push_back(new c_aptitude_unite("Maîtrise Dos",-1,"big_dos_m","chance",this));
    ui->layout_chance->insertWidget(4,map_unites["chance"]->last());
    map_unites["chance"]->push_back(new c_aptitude_unite("Maîtrise Berserk",-1,"big_berserk","chance",this));
    ui->layout_chance->insertWidget(5,map_unites["chance"]->last());
    map_unites["chance"]->push_back(new c_aptitude_unite("Maîtrise Soin",-1,"big_soin_m","chance",this));
    ui->layout_chance->insertWidget(6,map_unites["chance"]->last());
    map_unites["chance"]->push_back(new c_aptitude_unite("Résistance Dos",20,"big_dos_m","chance",this));
    ui->layout_chance->insertWidget(7,map_unites["chance"]->last());
    map_unites["chance"]->push_back(new c_aptitude_unite("Résistance Critique",20,"big_critique_r","chance",this));
    ui->layout_chance->insertWidget(8,map_unites["chance"]->last());

    map_unites["majeur"] = new QList<c_aptitude_unite*>;
    map_unites["majeur"]->push_back(new c_aptitude_unite("Point d'action",1,"big_pa","majeur",this));
    ui->layout_majeur->insertWidget(1,map_unites["majeur"]->last());
    map_unites["majeur"]->push_back(new c_aptitude_unite("Point de Mouvement et dégâts",1,"big_pm","majeur",this));
    ui->layout_majeur->insertWidget(2,map_unites["majeur"]->last());
    map_unites["majeur"]->push_back(new c_aptitude_unite("Portée et dégâts",1,"big_porte","majeur",this));
    ui->layout_majeur->insertWidget(3,map_unites["majeur"]->last());
    map_unites["majeur"]->push_back(new c_aptitude_unite("Point de Wakfu",1,"big_wakfu","majeur",this));
    ui->layout_majeur->insertWidget(4,map_unites["majeur"]->last());
    map_unites["majeur"]->push_back(new c_aptitude_unite("Contrôle et dégâts",1,"big_controle","majeur",this));
    ui->layout_majeur->insertWidget(5,map_unites["majeur"]->last());
    map_unites["majeur"]->push_back(new c_aptitude_unite("% Dommages infligés",1,"big_dommage","majeur",this));
    ui->layout_majeur->insertWidget(6,map_unites["majeur"]->last());
    map_unites["majeur"]->push_back(new c_aptitude_unite("Résistance Élémentaire majeur",1,"big_resistance","majeur",this));
    ui->layout_majeur->insertWidget(7,map_unites["majeur"]->last());

    foreach (QString key, map_unites.keys()) {
        QList<c_aptitude_unite*> list = *map_unites[key];
        foreach (c_aptitude_unite *unite, list) {
           QObject::connect(parent->getParent(),&MainWindow::shift_pressed,unite,&c_aptitude_unite::shift_pressed);
           QObject::connect(unite,&c_aptitude_unite::value_changed,this,&c_aptitudes_display::slot_value_changed);
           map_unites_all[unite->getType()] = unite;
        }
    }
    counts["intelligence"] = 10;
    counts["force"] = 10;
    counts["agilite"] = 10;
    counts["chance"] = 10;
    counts["majeur"] = 2;

    map_counts_labels["intelligence"]->setNum(counts["intelligence"]);
    map_counts_labels["force"]->setNum(counts["force"]);
    map_counts_labels["agilite"]->setNum(counts["agilite"]);
    map_counts_labels["chance"]->setNum(counts["chance"]);
    map_counts_labels["majeur"]->setNum(counts["majeur"]);
}

c_aptitudes_display::~c_aptitudes_display()
{
    delete ui;
}

int c_aptitudes_display::decrease(QString section) {
    if (counts[section] > 0) {
        counts[section]--;
        map_counts_labels[section]->setNum(counts[section]);
        if (counts[section] == 0) {
            QList<c_aptitude_unite*> list = *map_unites[section];
            for( int i = 0; i < list.size(); ++i) {
                list[i]->slot_setEnable_plus(false);
            }
        }
        return counts[section];
    }
    return -1;
}

int c_aptitudes_display::increase(QString section) {
    counts[section]++;
    map_counts_labels[section]->setNum(counts[section]);
    if (counts[section] != 0) {
        QList<c_aptitude_unite*>  list = *map_unites[section];
        for( int i = 0; i < list.size(); ++i) {
            list[i]->slot_setEnable_plus(true);
        }
    }
    return counts[section];
}

void c_aptitudes_display::compute_counts() {
    int status = 0;
    counts["intelligence"] = 0;
    counts["force"] = 0;
    counts["agilite"] = 0;
    counts["chance"] = 0;
    counts["majeur"] = 0;

    for (int i = 2; i <= lvl; ++i) {
        if (status == 0) {
            counts["intelligence"]++;
            status = 1;
        } else if (status == 1) {
            counts["force"]++;
            status = 2;
        } else if (status == 2) {
            counts["agilite"]++;
            status = 3;
        } else if (status == 3) {
            counts["chance"]++;
            status = 0;
        }
        if (i == 25 || i == 75 || i == 125 || i == 175) {
            counts["majeur"]++;
        }
    }
    if (lvl == 200) {
        counts["chance"]++;
    }

    map_counts_labels["intelligence"]->setNum(counts["intelligence"]);
    map_counts_labels["force"]->setNum(counts["force"]);
    map_counts_labels["agilite"]->setNum(counts["agilite"]);
    map_counts_labels["chance"]->setNum(counts["chance"]);
    map_counts_labels["majeur"]->setNum(counts["majeur"]);
}

void c_aptitudes_display::setLvl(int _lvl) {
    lvl = _lvl;
    reset();
    compute_counts();
}

void c_aptitudes_display::reset() {
    foreach (QString key, map_unites.keys()) {
        QList<c_aptitude_unite*> list = *map_unites[key];
        foreach (c_aptitude_unite *unite, list) {
           unite->reset();
        }
    }
}

void c_aptitudes_display::slot_value_changed(int value, QString type) {
    emit value_changed(type,value);
}

void c_aptitudes_display::slot_set_aptitudes(QMap<QString, int> bonuses) {
    foreach(QString key, bonuses.keys()) {
        map_unites_all[key]->setValue(bonuses[key]);
        emit value_changed(key,bonuses[key]);
    }
}


