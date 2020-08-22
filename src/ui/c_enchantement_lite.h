#ifndef C_ENCHANTEMENT_LITE_H
#define C_ENCHANTEMENT_LITE_H

#include <QWidget>
#include <QString>
#include "utilities/c_enchantement_effect.h"
#include "ui.h"

namespace Ui {
class c_enchantement_lite;
}

class c_enchantement_lite : public QWidget
{
    Q_OBJECT

public:
    explicit c_enchantement_lite(QWidget *parent = nullptr, c_enchantement_effect effect = c_enchantement_effect());
    ~c_enchantement_lite();

    int id() const;

    c_enchantement_effect effect() const;

public slots:
    void slot_highLight(bool flag);
    void slot_clicked();

signals:
    void clicked(int id);

private:
    Ui::c_enchantement_lite *ui;
    int _id;
    c_enchantement_effect _effect;
};

#endif // C_ENCHANTEMENT_LITE_H
