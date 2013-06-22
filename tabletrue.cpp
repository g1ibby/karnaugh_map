#include "tabletrue.h"

tableTrue::tableTrue() {
    symbol_num = 0;
    sp = 0;
    varible = new int[91];
    varible_num = 0;

    for (int i = 0; i < 50; i++)
        stack[i] = ' ';

    for (int i = 0; i < 91; i++)
            varible[i] = 0;
}

int tableTrue::PriorityOperation(char ch) {
    switch (ch) {
        case '(': return 0;
        case ')': return 1;
        case '+': return 2;
        case '&': return 3;
        case '!': return 4;
        case ' ':return -2;
        default: if ((int) ch >= 65 && (int) ch <= 90)
                return -1;
            else return 99; //код ошибки (ошибочный символ)
    }
}

int tableTrue::GetToken(char ch) {
    if (ch == '\n') //если конец ввода то
    {
        if (stack[symbol_num] != ' ') //если стек не пуст
            for (symbol_num; symbol_num >= 0; symbol_num--)
                opz[sp++] = stack[symbol_num]; //то выталкиваем все символы из стека
        return 0; //0-код завершения обработки
    }
    switch (PriorityOperation(ch)) //проверяет приоритет символа
    {
        case -1:
        {
        opz[sp++] = ch;
                    if (varible[(int) ch] != 1) {
                        varible[(int) ch]++;
                        varible_num++;
                    }
                    return 1;
        } //если это цифра
        case -2: return 1; //если пробел, пропускает его
        case 99: return -1;
        default: //если же это символ операции
            if (ch == ')') //если это закр. скобка
            {
                for (symbol_num; stack[symbol_num] != '('; symbol_num--) //выталкивает из стека все символы до (
                {
                    opz[sp++] = stack[symbol_num];
                    stack[symbol_num] = ' ';
                }
                stack[symbol_num--] = ' '; //стирает (
            } else {
                if (ch != '(' && stack[symbol_num] != ' ' && PriorityOperation(ch) <= PriorityOperation(stack[symbol_num])) { //иначе если это не (, стек не пуст и приоритет выше, чем у предыд.
                    int fl = 0;
                    for (symbol_num; fl == 0 && symbol_num >= 0; symbol_num--) //выталкивает символы из стека, пока не встретит символ с более выс. приоритетом
                    {
                        if (symbol_num != 0 && PriorityOperation(stack[symbol_num - 1]) < PriorityOperation(ch))
                            fl = 1;

                        opz[sp++] = stack[symbol_num];
                        stack[symbol_num] = ' ';
                    }
                    stack[++symbol_num] = ch; //записывает символ в стек
                } else {
                    if (stack[symbol_num] != ' ') { //иначе если стек не пуст
                        stack[++symbol_num] = ch; //записывает в стек и увеличивает i
                    } else {
                        stack[symbol_num] = ch; //если стек пуст, записывает без увеличения i
                    }
                }
            }
            return 1;
    }
}

bool tableTrue::CreateTable(QString bool_func) {
    bool_func = bool_func + '\n';
    for (int i = 0; i < bool_func.length(); i++) {
        char buf = bool_func.at(i).toLatin1();
        int result = GetToken(buf); //результат обработки очередного символа
        if (result == 0)
            break;
        if (result == -1) //-1-ошибка
        {
            throw -1;
            return false;
        } else continue; //иначе продолжение
    }

    int line_num = pow(2, varible_num);
    tableT = new bool *[line_num];
    for (int i = 0; i < line_num; i++) {
        tableT[i] = new bool[varible_num + 1];
    }
    for (int i = 0; i < line_num; i++) {
        for (int j = 0; j < varible_num + 1; j++) {
            tableT[i][j] = false;
        }
    }

    // Заполняем таблицу иситности начальными значениями
    for (int i = 0; i < line_num; i++) {
        int Dec = i;
        int j = varible_num - 1;
        while (Dec != 0) {
            tableT[i][j] = Dec % 2;
            Dec /= 2;
            j--;
        }
    }


    // Делаем назначение перменным нужного столбца
    int z = 0;
    for (int i = 0; i < 91; i++) {
        if (varible[i] == 1) {
            varible[i] = z + 1;
            z++;
        }
    }

    for (int i = 0; i < line_num; i++) {
        char opz_buf[100];
        for (int j = 0; j < sp; j++) {
            if ((int) opz[j] >= 65 && (int) opz[j] <= 90) {
                opz_buf[j] = tableT[i][varible[(int) opz[j]] - 1] + '0';
            } else {
                opz_buf[j] = opz[j];
            }
        }

        bool stack_int[100];
        int p = 0;
        for (int j = 0; j < sp; j++) {
            if (isalnum(opz_buf[j])) {
                char buf = opz_buf[j];
                stack_int[p++] = strtol(&buf, NULL, 10);
            } else {
                switch (opz_buf[j]) {
                    case '+':
                    {
                        stack_int[p - 2] = stack_int[p - 2] || stack_int[p - 1];
                        p--;
                        break;
                    }
                    case '&':
                    {
                        stack_int[p - 2] = stack_int[p - 2] && stack_int[p - 1];
                        p--;
                        break;
                    }
                    case '!':
                    {
                        stack_int[p - 1] = !stack_int[p - 1];
                        break;
                    }
                    default:
                    {
                        throw -1;
                        return false;

                    }
                }
            }
        }
        tableT[i][varible_num] = stack_int[p - 1];
    }

    return true;
}
