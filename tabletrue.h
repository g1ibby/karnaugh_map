#ifndef TABLETRUE_H
#define TABLETRUE_H

#include <QString>
#include <qmath.h>
#include <QVector>

using namespace std;
class tableTrue
{
public:
    tableTrue();
    bool CreateTable(QString bool_func);
    int  *varible;
    int varible_num;
    bool **tableT;

private:
    int symbol_num;
    int sp;
    char stack[100];
    char opz[100];
    int GetToken(char ch);
    int PriorityOperation(char ch);


};

#endif // TABLETRUE_H
