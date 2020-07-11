#ifndef C_CALCUL_H
#define C_CALCUL_H

#include <QObject>
#include <QtMath>
#include <QDebug>

class c_build;

class c_calcul : public QObject
{
    Q_OBJECT

public:
    c_calcul();
    static int compute_reduction(const int resistances);
    static int compute_life(const int niveau);
    void setBuild(c_build* build);

public slots:
    void computeMainMastery();
    void computeDamage(int attaqueValue);

private:
    c_build *_build;
    QList<QString> _mainMastery;
    QMap<QString,qreal> _damages;
    QString _healingElementMastery;
};

#endif // C_CALCUL_H
