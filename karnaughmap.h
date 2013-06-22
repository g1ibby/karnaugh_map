#ifndef KARNAUGHMAP_H
#define KARNAUGHMAP_H

#include <QString>
#include <qmath.h>

class karnaughMap
{
public:
    karnaughMap();
    bool createMap(bool **tableTrue, int varible_num);
    bool **karMap;
    int size_k_n;
    int size_k_m;

private:
    int grey(int n);
    int BinToDec(bool *bin, int n);
};

#endif // KARNAUGHMAP_H
