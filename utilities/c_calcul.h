#ifndef C_CALCUL_H
#define C_CALCUL_H

#include <QtMath>
#include <QDebug>

class c_calcul
{
public:
    c_calcul();
    int compute_reduction(const int resistances) const;
};

#endif // C_CALCUL_H
