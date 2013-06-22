#include "gminifunction.h"

gMiniFunction::gMiniFunction()
{

}

int gMiniFunction::grey(int n) {
    return n ^ (n >> 1);
}

string gMiniFunction::getMiniFunc(cover *KM_c, int c_size, int *var, int var_size, char type_form, int  len)
{

    char mark;
    char mark_2;
    if (type_form == 'D')
    {
        mark = '+';
        mark_2 = '&';
    }
    else
    {
        mark = '&';
        mark_2 = '+';
    }
    string mini_func;
        for (int i = 0; i < c_size; i++) {
            bool flg_iml = false;
            bool mini[100][len];
            for (int j = 0; j < 20; j++) {
                for (int k = 0; k < len; k++) {
                    mini[j][k] = false;
                }
            }
            int mini_i = 0;
            int mini_j = 0;

            for (int j = 0; j < KM_c[i].size; j++) {
                int g = grey(KM_c[i].elements[j][0]);
                int mini_j = len - 1;
                while (g != 0) {
                    mini[mini_i][mini_j] = g % 2;
                    g /= 2;
                    mini_j--;
                }

                g = grey(KM_c[i].elements[j][1]);
                while (g != 0) {
                    mini[mini_i][mini_j] = g % 2;
                    g /= 2;
                    mini_j--;
                }
                mini_i++;
            }

            for (int j = 0; j < len; j++) {
                bool flg_null = false;
                bool flg_one = false;

                for (int k = 0; k < mini_i; k++) {
                    if (mini[k][j] == true) {
                        flg_one = true;
                    } else {
                        flg_null = true;
                    }
                }

                char temp;
                int o = 0;
                for (int k = 0; k < 91; k++) {
                    if (var[k] > 0) {
                        o++;
                        temp = (char)k;
                    }
                    if (o == j+1) {
                        break;
                    }
                }

                if (mini_func == "")
                {
                    if (flg_one == true && flg_null == false) {
                        mini_func = mini_func + temp;
                    } else if (flg_null == true && flg_one == false) {
                        mini_func = mini_func + "!" + temp;
                    }
                }
                else
                {
                    char buf_mark = mark_2;
                    if (flg_iml == false)
                    {
                        buf_mark = ' ';
                    }
                    if (flg_one == true && flg_null == false) {
                        mini_func = mini_func + buf_mark + temp;
                    } else if (flg_null == true && flg_one == false) {
                        mini_func = mini_func + buf_mark + " !" + temp;
                    }
                }

            }

            mini_func = mini_func + ' ' + mark + ' ';
        }

        mini_func.erase(mini_func.size()-2, 2);
            return mini_func;
}
