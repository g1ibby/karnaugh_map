#ifndef GMINIFUNCTION_H
#define GMINIFUNCTION_H

#include <string>
#include "searchcoating.h"

class gMiniFunction
{
public:
    gMiniFunction();
    string getMiniFunc(cover *KM_c, int c_size, int *var, int var_size, char type_form, int len);
private:
    int grey(int n);
};

#endif // GMINIFUNCTION_H
