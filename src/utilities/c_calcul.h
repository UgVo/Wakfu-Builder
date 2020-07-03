#ifndef C_CALCUL_H
#define C_CALCUL_H

#include <QtMath>
#include <QDebug>

class c_calcul
{
public:
    c_calcul();
    static int compute_reduction(const int resistances);
    static int compute_life(const int niveau);
};

#endif // C_CALCUL_H
