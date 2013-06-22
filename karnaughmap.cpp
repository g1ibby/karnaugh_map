#include "karnaughmap.h"


karnaughMap::karnaughMap()
{
}

int karnaughMap::grey(int n) {
    return n ^ (n >> 1);
}

int karnaughMap::BinToDec(bool *bin, int n) {
    int dec = 0;
    for (int k = 0; k < n; k++) {
        dec = dec * 2 + bin[k];
    }

    return dec;
}

bool karnaughMap::createMap(bool **tableTrue, int varible_num) {
    int km_n, km_m, km_n_v, km_m_v;
    if ((varible_num % 2) == 0) {
        km_n = pow(2, (varible_num / 2));
        km_n_v = varible_num / 2;
        km_m = pow(2, (varible_num / 2));
        km_m_v = varible_num / 2;
    } else {
        km_n = pow(2, (varible_num / 2));
        km_n_v = varible_num / 2;
        km_m = pow(2, (varible_num / 2) + 1);
        km_m_v = (varible_num / 2)+ 1;
    }
    karMap = new bool *[km_n];
    for (int i = 0; i < km_n; i++) {
        karMap[i] = new bool[km_m];
    }
    size_k_n = km_n;
    size_k_m = km_m;
    for (int k = 0; k < km_n; k++) {
        for (int j = 0; j < km_m; j++) {
            karMap[k][j] = 0;
        }
    }

    for (int k = 0; k < km_n; k++) {
        for (int j = 0; j < km_m; j++) {
            bool grey_cod[km_n_v + km_m_v];
            for (int r = 0; r < km_n_v + km_m_v; r++) {
                grey_cod[r] = 0;
            }

            int g = grey(k);
            int o = km_n_v - 1;

            while (g != 0) {
                grey_cod[o] = g % 2;
                g /= 2;
                o--;
            }

            g = grey(j);
            o = (km_n_v + km_m_v) - 1;

            while (g != 0) {
                grey_cod[o] = g % 2;
                g /= 2;
                o--;
            }

            karMap[k][j] = tableTrue[BinToDec(grey_cod, km_n_v + km_m_v)][varible_num];

        }
    }

    return true;
}
