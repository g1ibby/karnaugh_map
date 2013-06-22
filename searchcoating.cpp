#include "searchcoating.h"

#define GetIndex(_index,_size) ( ( (_index%_size) + _size )%_size )

searchCoating::searchCoating()
{
    KM_cover = new cover[100];
    cover_size = 0;
}

bool searchCoating::IncludCell(int x, int y, int hight, int width) {
    for (int i = 0; i < cover_size; i++) {
        for (int j = 0; j < KM_cover[i].size; j++) {
            if ((x == GetIndex(KM_cover[i].elements[j][0], hight)) && (y == GetIndex(KM_cover[i].elements[j][1], width))) {
                return true;
            }
        }
    }
    return false;
}

int searchCoating::NumberFireOne(cover c) {
    int num = 0;
    bool flg = false;
    for (int i = 0; i < c.size; i++) {
        for (int j = 0; j < cover_size; j++) {
            for (int k = 0; k < KM_cover[j].size; k++) {
                if ((KM_cover[j].elements[k][0] == c.elements[i][0]) && (KM_cover[j].elements[k][1] == c.elements[i][1])) {
                    num++;
                    flg = true;
                    break;
                }
            }
            if (flg == true) {
                flg = false;
                break;
            }
        }
    }
    return num;
}

bool searchCoating::IncludIN(int x_temp, int y_temp, cover c) {
    for (int i = 0; i < c.size; i++) {
        if ((c.elements[i][0] == x_temp) && (c.elements[i][1] == y_temp)) {
            return true;
        }
    }
    return false;
}

bool searchCoating::CompareCoverage() {
    if (coverTemp.size >= coverBest.size) { // Данная склейка по площаде больше или равна лучшей
        if (coverTemp.size == coverBest.size) { // Данная слкейка по площаде равна лучшей
            if (NumberFireOne(coverTemp) < NumberFireOne(coverBest)) { // Данное покрытие покрывает меньше единиц уже покрытих другими склейками
                coverBest = coverTemp; // Данная слкейка становится лучшей
            }
        } else {
            coverBest = coverTemp; // Данная слкейка становится лучшей
        }
    }
}

string searchCoating::to_string(int number) {
    string number_string = "";
    char ones_char;
    int ones = 0;
    while (true) {
        ones = number % 10;
        switch (ones) {
            case 0: ones_char = '0';
                break;
            case 1: ones_char = '1';
                break;
            case 2: ones_char = '2';
                break;
            case 3: ones_char = '3';
                break;
            case 4: ones_char = '4';
                break;
            case 5: ones_char = '5';
                break;
            case 6: ones_char = '6';
                break;
            case 7: ones_char = '7';
                break;
            case 8: ones_char = '8';
                break;
            case 9: ones_char = '9';
                break;
        }
        number -= ones;
        number_string = ones_char + number_string;
        if (number == 0) {
            break;
        }
        number = number / 10;
    }
    return number_string;
}

bool searchCoating::getTypeFrom() { // Функция определяет к какой форме лучше минимизировать функциюы
    int one = 0;
    int null = 0;

    for (int i = 0; i < KM_hight_global; i++) {
        for (int j = 0; j < KM_width_global; j++) {
            if (KM[i][j] == true) {
                one++;
            } else {
                null++;
            }
        }
    }

    if (one >= null) {
        return true;
    } else {
        return false;
    }
}

int searchCoating::VerLocalRight(int max_cover/*максимальный размер склейки*/,
        int restriction/*конечный элемент*/,
        bool avoidant/*Замкнутость*/,
        int axis/*Ось симметрии*/, int KM_width, int KM_hight) {
    int k = 1;
    int x_offset = 0;
    int location_coverage = GetIndex(coverTemp.x, KM_width_global) + (coverTemp.size_width - 1); // Расположение последнего элемента из покрытия


    int distance_from_axis = axis - (GetIndex(coverTemp.x, KM_width_global) + (coverTemp.size_width - 1));
    if (distance_from_axis < 0) {
        return 0;
    }
    while (k <= distance_from_axis/*растояние которое нужно пройти до оси симметрии*/ + (coverTemp.size_width) + distance_from_axis/*растояние после оси симметрии*/) {

        if ((avoidant != true) && (location_coverage + 1 + x_offset > restriction)) {
            return 0;
        }

        for (int i = 0; i < coverTemp.size_hight; i++) {
            int a = GetIndex(GetIndex(coverTemp.y, KM_hight_global) + i, KM_hight_global);
            int b = GetIndex(location_coverage + x_offset + 1, KM_width_global);
            if ((KM[a][b] != typeForm) || IncludIN(a, b, coverTemp) == true) {
                return 0;
            }
        }
        x_offset++;
        k++;
    }

    return x_offset;
}

int searchCoating::VerLocalBottom(int max_cover/*максимальный размер склейки*/,
        int restriction/*конечный элемент*/,
        bool avoidant/*Замкнутость*/,
        int axis/*Ось симметрии*/, int KM_width, int KM_hight) {

    int k = 1;
    int y_offset = 0;
    int location_coverage = GetIndex(coverTemp.y, KM_hight_global) + (coverTemp.size_hight - 1); // Расположение последнего элемента из покрытия

    int distance_from_axis = axis - (GetIndex(coverTemp.y, KM_hight_global) + (coverTemp.size_hight - 1));
    if (distance_from_axis < 0) {
        return 0;
    }
    while (k <= distance_from_axis/*растояние которое нужно пройти до оси симметрии*/ + (coverTemp.size_hight) + distance_from_axis/*растояние после оси симметрии*/) {

        if ((avoidant != true) && (location_coverage + 1 + y_offset > restriction)) {
            return 0;
        }

        for (int i = 0; i < coverTemp.size_width; i++) {
            int a = GetIndex(location_coverage + y_offset + 1, KM_hight_global);
            int b = GetIndex(GetIndex(coverTemp.x, KM_width_global) + i, KM_width_global);

            if ((IncludIN(a, b, coverTemp) == true) || (KM[a][b] != typeForm)) {
                return 0;
            }
        }
        y_offset++;
        k++;
    }

    return y_offset;
}

int searchCoating::VerLocalLeft(int max_cover/*максимальный размер склейки*/,
        int restriction/*конечный элемент*/,
        bool avoidant/*Замкнутость*/,
        int axis/*Ось симметрии*/, int KM_width, int KM_hight) {

    int k = 1;
    int x_offset = 0;
    int location_coverage = GetIndex(coverTemp.x, KM_width_global); // Расположение последнего элемента из покрытия

    int distance_from_axis = (GetIndex(coverTemp.x, KM_width_global)) - axis;
    if (distance_from_axis < 0) {
        return 0;
    }
    while (k <= distance_from_axis/*растояние которое нужно пройти до оси симметрии*/ + (coverTemp.size_width) + distance_from_axis/*растояние после оси симметрии*/) {

        if ((avoidant != true) && (location_coverage - 1 - x_offset < restriction)) {
            return 0;
        }

        for (int i = 0; i < coverTemp.size_hight; i++) {
            int a = GetIndex(GetIndex(coverTemp.y, KM_hight_global) + i, KM_hight_global);
            int b = GetIndex(location_coverage - x_offset - 1, KM_width_global);
            if ((KM[a][b] != typeForm) || IncludIN(a, b, coverTemp) == true) {
                return 0;
            }
        }
        x_offset++;
        k++;
    }

    return x_offset;
}

int searchCoating::VerLocalTop(int max_cover/*максимальный размер склейки*/,
        int restriction/*конечный элемент*/,
        bool avoidant/*Замкнутость*/,
        int axis/*Ось симметрии*/, int KM_width, int KM_hight) {

    int k = 1;
    int y_offset = 0;
    int location_coverage = GetIndex(coverTemp.y, KM_hight_global); // Расположение последнего элемента из покрытия

    int distance_from_axis = (GetIndex(coverTemp.y, KM_hight_global)) - axis;
    if (distance_from_axis < 0) {
        return 0;
    }
    while (k <= distance_from_axis/*растояние которое нужно пройти до оси симметрии*/ + (coverTemp.size_hight) + distance_from_axis/*растояние после оси симметрии*/) {

        if ((avoidant != true) && (location_coverage - 1 - y_offset < restriction)) {
            return 0;
        }

        for (int i = 0; i < coverTemp.size_width; i++) {
            int a = GetIndex(location_coverage - y_offset - 1, KM_hight_global);
            int b = GetIndex(GetIndex(coverTemp.x, KM_width_global) + i, KM_width_global);

            if ((IncludIN(a, b, coverTemp) == true) || (KM[a][b] != typeForm)) {
                return 0;
            }
        }
        y_offset++;
        k++;
    }

    return y_offset;
}

bool searchCoating::SearchLocalOptimalCover(int KM_local_hight, int KM_local_width, int b_x, int b_y, bool av) {


    cover coverBuf;
    /*Данные переменные нужны для правильной рекурсии*/
    int KM_local_hight_temp = KM_local_hight; // Высота карты карно
    int KM_local_width_temp = KM_local_width; // Ширина карты карно
    int b_x_temp = b_x; // Где начинается карта карно в соотвецтвии с новой системой координат
    int b_y_temp = b_y;
    bool av_temp = av;

    int rise = 0; // Количиство допустимых шагов для покрытия

    /*Максимальный размер который может покрыть склейка(размер задан в количистве перменных в карте карно)*/
    int max_cover = log(KM_local_hight) / log(2) + log(KM_local_width) / log(2);

    // Проверяем возможность движения вправо
    rise = VerLocalRight(max_cover, b_x + (KM_local_width - 1)/*Последний элемент который может быть покрыт данной склейкой*/
            , av/*Замкнутость карты карно*/
            , GetIndex(coverTemp.x, KM_width_global) + (coverTemp.size_width - 1)/*локальная ось симметрии относительно которой будет проверятся возможность роста*/,
            KM_local_width, KM_local_hight);
    if (rise != 0) {
        coverBuf = coverTemp;
        // Производим рост покрытия coverTemp в право
        for (int i = 0; i < rise; i++) {
            for (int j = 0; j < coverTemp.size_hight; j++) {
                coverTemp.elements[coverTemp.size][0] = coverTemp.y + j;
                coverTemp.elements[coverTemp.size][1] = coverTemp.x + coverTemp.size_width;

                coverTemp.size++;
            }
            coverTemp.size_width++;
        }

        SearchLocalOptimalCover(KM_local_hight_temp, KM_local_width_temp, b_x_temp, b_y_temp, av_temp); // Рекурсивный вызов функции
        coverTemp = coverBuf; // Возрощаемся к склейки до роста вправо
    }

    // Проверяем возможность движения вниз
    rise = 0;
    rise = VerLocalBottom(max_cover, b_y + (KM_local_hight - 1)/*Последний элемент который может быть покрыт данной склейкой*/
            , av/*Замкнутость карты карно*/
            , GetIndex(coverTemp.y, KM_hight_global) + (coverTemp.size_hight - 1)/*локальная ось симметрии относительно которой будет проверятся возможность роста*/,
            KM_local_width, KM_local_hight);
    if (rise != 0) {
        coverBuf = coverTemp;
        // Производим рост покрытия coverTemp вниз
        for (int i = 0; i < rise; i++) {
            for (int j = 0; j < coverTemp.size_width; j++) {
                coverTemp.elements[coverTemp.size][0] = coverTemp.y + coverTemp.size_hight;
                coverTemp.elements[coverTemp.size][1] = coverTemp.x + j;

                coverTemp.size++;
            }
            coverTemp.size_hight++;
        }

        SearchLocalOptimalCover(KM_local_hight_temp, KM_local_width_temp, b_x_temp, b_y_temp, av_temp); // Рекурсивный вызов функции
        coverTemp = coverBuf; // Возрощаемся к склейки до роста вправо
    }


    // Проверяем возможность движения влево
    rise = 0;
    rise = VerLocalLeft(max_cover, b_x/*Последний элемент который может быть покрыт данной склейкой*/
            , av/*Замкнутость карты карно*/
            , GetIndex(coverTemp.x, KM_width_global)/*локальная ось симметрии относительно которой будет проверятся возможность роста*/,
            KM_local_width, KM_local_hight);
    if (rise != 0) {
        coverBuf = coverTemp;
        // Производим рост покрытия coverTemp влево
        for (int i = 0; i < rise; i++) {
            coverTemp.x--;
            for (int j = 0; j < coverTemp.size_hight; j++) {
                coverTemp.elements[coverTemp.size][0] = coverTemp.y + j;
                coverTemp.elements[coverTemp.size][1] = coverTemp.x;

                coverTemp.size++;
            }
            coverTemp.size_width++;

        }

        SearchLocalOptimalCover(KM_local_hight_temp, KM_local_width_temp, b_x_temp, b_y_temp, av_temp); // Рекурсивный вызов функции
        coverTemp = coverBuf; // Возрощаемся к склейки до роста вправо
    }

    // Проверяем возможность движения вверх
    rise = 0;
    rise = VerLocalTop(max_cover, b_y/*Последний элемент который может быть покрыт данной склейкой*/
            , av/*Замкнутость карты карно*/
            , GetIndex(coverTemp.y, KM_hight_global)/*локальная ось симметрии относительно которой будет проверятся возможность роста*/,
            KM_local_width, KM_local_hight);
    if (rise != 0) {
        coverBuf = coverTemp;
        // Производим рост покрытия coverTemp вверх
        for (int i = 0; i < rise; i++) {
            coverTemp.y--;
            for (int j = 0; j < coverTemp.size_width; j++) {
                coverTemp.elements[coverTemp.size][0] = coverTemp.y;
                coverTemp.elements[coverTemp.size][1] = coverTemp.x + j;

                coverTemp.size++;
            }

            coverTemp.size_hight++;
        }

        SearchLocalOptimalCover(KM_local_hight_temp, KM_local_width_temp, b_x_temp, b_y_temp, av_temp); // Рекурсивный вызов функции
        coverTemp = coverBuf; // Возрощаемся к склейки до роста вправо
    }

    CompareCoverage(); // Производим сравнение текущей склейки с лучшей в случаии если она лучше то происходит замена

}

bool searchCoating::searchLocalCoating(int KM_hight, int KM_width, int begin_x, int begin_y, bool avoid) { // Производит локальный поиск

    for (int i = 0; i < KM_hight; i++) {
        for (int j = 0; j < KM_width; j++) {
            if (KM[i + begin_y][j + begin_x] == typeForm && IncludCell(i + begin_y, j + begin_x, KM_hight_global, KM_width_global) == false) {

                coverTemp = {1, GetIndex(j + begin_x, KM_width_global), GetIndex(i + begin_y, KM_hight_global), 1, 1, {
                        {GetIndex(i + begin_y, KM_hight_global), GetIndex(j + begin_x, KM_width_global)}
                    }};

                coverBest = {1, GetIndex(j + begin_x, KM_width_global), GetIndex(i + begin_y, KM_hight_global), 1, 1, {
                        {GetIndex(i + begin_y, KM_hight_global), GetIndex(j + begin_x, KM_width_global)}
                    }};
                SearchLocalOptimalCover(KM_hight, KM_width, begin_x, begin_y, avoid); // Поиск оптимальной склейкии для данной точки
                KM_cover[cover_size] = coverBest;
                cover_size++;
            }
        }
    }
    NormalizedBasis();
}

bool searchCoating::NormalizedBasis() {
    // Преобразуем координаты покрытий в нормальный базис
    for (int i = 0; i < cover_size; i++) {
        for (int j = 0; j < KM_cover[i].size; j++) {
            KM_cover[i].elements[j][0] = GetIndex(KM_cover[i].elements[j][0], KM_hight_global);
            KM_cover[i].elements[j][1] = GetIndex(KM_cover[i].elements[j][1], KM_width_global);
        }
        KM_cover[i].x = GetIndex(KM_cover[i].x, KM_width_global);
        KM_cover[i].y = GetIndex(KM_cover[i].y, KM_hight_global);
    }
}

bool searchCoating::createAxisSymmetry() { // Функция создает массив с осями симметрии

    int size_x = KM_width_global / 4;
    int size_y = KM_hight_global / 4;
    size_symmetry_x = 0;
    size_symmetry_y = 0;

    for (int i = 0; i < size_x; i++) {
        axisSymmetry[0][i] = ((i + 1) * 4) - 1;
        size_symmetry_x++;
    }
    for (int i = 0; i < size_y; i++) {
        axisSymmetry[1][i] = ((i + 1) * 4) - 1;
        size_symmetry_y++;
    }
}

bool searchCoating::SearchAxles() {

    /*Максимальный размер который может покрыть склейка(размер задан в количистве перменных в карте карно)*/
    int max_cover = log(KM_hight_global) / log(2) + log(KM_width_global) / log(2);

    for (int k = 0; k < size_symmetry_x; k++) {
        int rise = VerLocalRight(max_cover, 0/*Последний элемент который может быть покрыт данной склейкой*/
                , true/*Замкнутость карты карно*/
                , GetIndex(axisSymmetry[0][k], KM_width_global)/*глобальная ось симметрии относительно которой будет проверятся возможность роста*/,
                KM_width_global, KM_hight_global);
        if (rise != 0) {
            cover coverBuf = coverTemp;
            // Производим рост покрытия coverTemp в право
            for (int i = 0; i < rise; i++) {
                for (int j = 0; j < coverTemp.size_hight; j++) {
                    coverTemp.elements[coverTemp.size][0] = coverTemp.y + j;
                    coverTemp.elements[coverTemp.size][1] = coverTemp.x + coverTemp.size_width;

                    coverTemp.size++;
                }
                coverTemp.size_width++;
            }

            SearchAxles(); // Рекурсивный вызов функции
            coverTemp = coverBuf; // Возрощаемся к склейки до роста вправо
        }
    }

    for (int k = 0; k < size_symmetry_y; k++) {
        int rise = VerLocalBottom(max_cover, 0/*Последний элемент который может быть покрыт данной склейкой*/
                , true/*Замкнутость карты карно*/
                , GetIndex(axisSymmetry[1][k], KM_hight_global)/*глобальная ось симметрии относительно которой будет проверятся возможность роста*/,
                KM_width_global, KM_hight_global);
        if (rise != 0) {
            cover coverBuf = coverTemp;
            // Производим рост покрытия coverTemp вниз
            for (int i = 0; i < rise; i++) {
                for (int j = 0; j < coverTemp.size_width; j++) {
                    coverTemp.elements[coverTemp.size][0] = coverTemp.y + coverTemp.size_hight;
                    coverTemp.elements[coverTemp.size][1] = coverTemp.x + j;

                    coverTemp.size++;
                }
                coverTemp.size_hight++;
            }

            SearchAxles(); // Рекурсивный вызов функции
            coverTemp = coverBuf; // Возрощаемся к склейки до роста вправо
        }
    }

    for (int k = 0; k < size_symmetry_x; k++) {
        int rise = VerLocalLeft(max_cover, 0/*Последний элемент который может быть покрыт данной склейкой*/
                , true/*Замкнутость карты карно*/
                , GetIndex(axisSymmetry[0][k] + 1, KM_width_global)/*глобальная ось симметрии относительно которой будет проверятся возможность роста*/,
                KM_width_global, KM_hight_global);
        if (rise != 0) {
            cover coverBuf = coverTemp;
            // Производим рост покрытия coverTemp влево
            for (int i = 0; i < rise; i++) {
                coverTemp.x--;
                for (int j = 0; j < coverTemp.size_hight; j++) {
                    coverTemp.elements[coverTemp.size][0] = coverTemp.y + j;
                    coverTemp.elements[coverTemp.size][1] = coverTemp.x;

                    coverTemp.size++;
                }
                coverTemp.size_width++;

            }

            SearchAxles(); // Рекурсивный вызов функции
            coverTemp = coverBuf; // Возрощаемся к склейки до роста вправо
        }
    }

    for (int k = 0; k < size_symmetry_y; k++) {
        int rise = VerLocalTop(max_cover, 0/*Последний элемент который может быть покрыт данной склейкой*/
                , true/*Замкнутость карты карно*/
                , GetIndex(axisSymmetry[1][k] + 1, KM_hight_global)/*локальная ось симметрии относительно которой будет проверятся возможность роста*/,
                KM_width_global, KM_hight_global);
        if (rise != 0) {
            cover coverBuf = coverTemp;
            // Производим рост покрытия coverTemp вверх
            for (int i = 0; i < rise; i++) {
                coverTemp.y--;
                for (int j = 0; j < coverTemp.size_width; j++) {
                    coverTemp.elements[coverTemp.size][0] = coverTemp.y;
                    coverTemp.elements[coverTemp.size][1] = coverTemp.x + j;

                    coverTemp.size++;
                }

                coverTemp.size_hight++;
            }

            SearchAxles(); // Рекурсивный вызов функции
            coverTemp = coverBuf; // Возрощаемся к склейки до роста вправо
        }
    }

    CompareCoverage(); // Производим сравнение текущей склейки с лучшей в случаии если она лучше то происходит замена

}

bool searchCoating::DeleteCover(int index) {
    for (int i = index; i < cover_size; i++) {
        KM_cover[i] = KM_cover[i + 1];
    }
    cover_size--;
    return true;
}

bool searchCoating::DeleteRedundancy() {
    int i = 0;
    while (i < cover_size) {
        int flg = 0;
        for (int j = 0; j < cover_size; j++) {
            if (i != j) {
                for (int k = 0; k < KM_cover[i].size; k++) {
                    if (IncludIN(KM_cover[i].elements[k][0], KM_cover[i].elements[k][1], KM_cover[j]) == true) {
                        flg++;
                    } else {
                        flg = 0;
                        break;
                    }
                }

                if ((flg == KM_cover[j].size) && (flg != 0)) {
                    DeleteCover(i);
                    break;
                }
            }
        }
        if (flg == 0) {
            i++;
        }
    }
    return true;
}

bool searchCoating::getCover(bool **KM_temp, int KM_hight, int KM_width, char typeCover) {
    // D - ДНФ
    // K - КНФ
    // A - определить автоматичиски
    // Делаем переданные парметры глобальными для удобства
    KM = KM_temp;
    KM_hight_global = KM_hight;
    KM_width_global = KM_width;

    // Определим к какой форме будем преобразовывать формулы
    if (typeCover == 'D') {
        typeForm = true; // Функция будет минимизирована к виду ДНФ
    } else if (typeCover == 'K') {
        typeForm = false; // Функция будет минимизирована к виду КНФ
    } else if (typeCover == 'A') {
        typeForm = getTypeFrom(); // Автоматичиски определим к какой форме будет лучше привести формулу
    }

    if (KM_hight_global <= 4 && KM_width_global <= 4) {
        if (KM_hight_global < 2 || KM_width_global < 2) {
            throw -1; // Завершаемся с ошибкой если некоректный размер карты карно
            return false;
        }
        // Вызываем функцию для поиска покрытий в карте которая меньше 4
        searchLocalCoating(KM_hight_global, KM_width_global, 0, 0, true); // !!! Если количиство переменных 3; не получится замкнутость карты карно
        DeleteRedundancy(); // Удаляем избыточные покрытия
        return true;
    }

    // Если переменных больше 4 тогда разбиваем карту на области 4x4
    createAxisSymmetry();

    // Осущиствим просмотр квадратов 4x4 и локальный поиск в каждом из них
    for (int i = 0; i < KM_hight_global / 4; i++) {
        for (int j = 0; j < KM_width_global / 4; j++) {
            searchLocalCoating(4, 4, j * 4, i * 4, false);
        }
    }

    DeleteRedundancy(); // Удаляем избыточные покрытия



    /*----------------------------------------------------------*/

    for (int i = 0; i < cover_size; i++) {
        coverTemp = KM_cover[i];
        coverBest = KM_cover[i];
        SearchAxles();

        KM_cover[i] = coverBest;
    }
    NormalizedBasis();  // Нормализируем координаты в нормальный базис
    DeleteRedundancy(); // Удаляем избыточные покрытия


}
