#ifndef C_THEORY_CRAFT_RESUME_H
#define C_THEORY_CRAFT_RESUME_H

#include <QWidget>
#include <QMap>
#include <QString>
#include <QtMath>
#include "ui.h"

namespace Ui {
class c_theory_craft_resume;
}

class c_theory_craft_resume : public QWidget
{
    Q_OBJECT

public:
    explicit c_theory_craft_resume(QWidget *parent = nullptr);
    ~c_theory_craft_resume();

    void setValues(QMap<QString,qreal> values);
    void updateView();

private:
    Ui::c_theory_craft_resume *ui;
    QMap<QString,qreal> values;
};

#endif // C_THEORY_CRAFT_RESUME_H
