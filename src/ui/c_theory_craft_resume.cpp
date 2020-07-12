#include "c_theory_craft_resume.h"
#include "ui_c_theory_craft_resume.h"

c_theory_craft_resume::c_theory_craft_resume(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::c_theory_craft_resume)
{
    ui->setupUi(this);

    ui->tabWidget_resume->setStyleSheet(QString( "QTabWidget::pane {"
                                                 "  border: 0px solid black; "
                                                 "  border-radius: 3px; "
                                                 "  border-top-left-radius: 0px; "
                                                 "  background: %1;"
                                                 "} "
                                                 "QTabBar::tab {"
                                                 "  border: 0px solid black; "
                                                 "  border-bottom-left-radius: 3px; "
                                                 "  border-top-left-radius: 3px; "
                                                 "  height: 60px;"
                                                 "  width: 30px;"
                                                 "  background: %1;"
                                                 "  color : white;"
                                                 "} "
                                                 "QTabBar::tab:!selected {"
                                                 "  background: %2;"
                                                 "}"
                                                 "QLabel {"
                                                 "  color: white;"
                                                 "}").arg(app_color::dark_blue).arg(app_color::grey_blue_3));
}

c_theory_craft_resume::~c_theory_craft_resume()
{
    delete ui;
}

void c_theory_craft_resume::setValues(QMap<QString,qreal> _values) {
    values = _values;
    updateView();
}

void c_theory_craft_resume::updateView() {
    ui->label_back->setNum(qFloor(values["Back"]));
    ui->label_back_critique->setNum(qFloor(values["Back Critique"]));
    ui->label_back_moyen->setNum(qFloor(values["Back Mean"]));
    ui->label_front->setNum(qFloor(values["Front"]));
    ui->label_front_critique->setNum(qFloor(values["Front Critique"]));
    ui->label_front_moyen->setNum(qFloor(values["Front Mean"]));
    ui->label_soin->setNum(qFloor(values["Heal"]));
    ui->label_soin_critique->setNum(qFloor(values["Heal Critique"]));
    ui->label_soin_moyen->setNum(qFloor(values["Heal Mean"]));

    ui->label_back_2->setNum(qFloor(values["Berserk Back"]));
    ui->label_back_critique_2->setNum(qFloor(values["Berserk Back Critique"]));
    ui->label_back_moyen_2->setNum(qFloor(values["Berserk Back Mean"]));
    ui->label_front_2->setNum(qFloor(values["Berserk Front"]));
    ui->label_front_critique_2->setNum(qFloor(values["Berserk Front Critique"]));
    ui->label_front_moyen_2->setNum(qFloor(values["Berserk Front Mean"]));
    ui->label_soin_2->setNum(qFloor(values["Berserk Heal"]));
    ui->label_soin_critique_2->setNum(qFloor(values["Berserk Heal Critique"]));
    ui->label_soin_moyen_2->setNum(qFloor(values["Berserk Heal Mean"]));
}
