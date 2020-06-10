#ifndef C_APTITUDE_UNITE_H
#define C_APTITUDE_UNITE_H

#include <QWidget>
#include <QKeyEvent>

class c_aptitudes_display;

namespace Ui {
class c_aptitude_unite;
}

class c_aptitude_unite : public QWidget
{
    Q_OBJECT

public:
    explicit c_aptitude_unite(QString text, int max, QString image_name, QString section, QWidget *parent = nullptr);
    ~c_aptitude_unite();
    void enable_minus(bool enable);

    QString getType() const;

    void setValue(int value);

private:
    Ui::c_aptitude_unite *ui;
    c_aptitudes_display *parent;
    QString type;
    QString section;
    int value;
    int max;
    bool pack_increase;

public slots:
    void slot_setEnable_plus(bool enable);
    void slot_plus_clicked();
    void slot_minus_clicked();
    void shift_pressed(bool state);
    void reset();
//    virtual void keyPressEvent(QKeyEvent *event);
//    virtual void keyReleaseEvent(QKeyEvent *event);

signals:
    void value_changed(int value, QString type);
};

#endif // C_APTITUDE_UNITE_H
