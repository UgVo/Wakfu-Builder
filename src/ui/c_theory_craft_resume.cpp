#include "c_theory_craft_resume.h"
#include "ui_c_theory_craft_resume.h"

c_theory_craft_resume::c_theory_craft_resume(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::c_theory_craft_resume)
{
    ui->setupUi(this);
}

c_theory_craft_resume::~c_theory_craft_resume()
{
    delete ui;
}
