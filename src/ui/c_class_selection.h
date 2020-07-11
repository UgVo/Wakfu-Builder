#ifndef C_CLASS_SELECTION_H
#define C_CLASS_SELECTION_H

#include <QWidget>
#include <QToolButton>
#include "ui.h"

namespace Ui {
class c_class_selection;
}

class c_class_selection : public QWidget
{
    Q_OBJECT

public:
    explicit c_class_selection(QWidget *parent = nullptr);
    ~c_class_selection();

private:
    Ui::c_class_selection *ui;
    void setButtonStyle(QToolButton *pb);

public slots:
    void slot_update_genre();
    void slot_class_chosen();
    void slot_canceled();

signals:
    void class_chosen(int id);
    void rejected();
};

#endif // C_CLASS_SELECTION_H
