#ifndef C_THEORY_CRAFT_RESUME_H
#define C_THEORY_CRAFT_RESUME_H

#include <QWidget>

namespace Ui {
class c_theory_craft_resume;
}

class c_theory_craft_resume : public QWidget
{
    Q_OBJECT

public:
    explicit c_theory_craft_resume(QWidget *parent = nullptr);
    ~c_theory_craft_resume();

private:
    Ui::c_theory_craft_resume *ui;
};

#endif // C_THEORY_CRAFT_RESUME_H
