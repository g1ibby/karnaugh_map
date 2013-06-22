#ifndef SEARCHCOATING_H
#define SEARCHCOATING_H

#include <QString>
#include <qmath.h>

struct cover {
    int size;

    int x;
    int y;

    int size_hight;
    int size_width;

    int elements[100][2];
};

using namespace std;

class searchCoating
{
public:
    searchCoating();
    bool **KM;
    int KM_hight_global;
    int KM_width_global;
    int cover_size;
    cover *KM_cover;
    bool typeForm;

    int size_symmetry_x;
    int size_symmetry_y;
    int axisSymmetry[2][10];

    bool getCover(bool **KM_temp, int KM_hight, int KM_width, char typeCover);

private:
    bool IncludCell(int x, int y, int hight, int width);
        int NumberFireOne(cover c);
        bool CompareCoverage();
        string to_string(int number);
        bool getTypeFrom();
        bool searchLocalCoating(int KM_hight, int KM_width, int begin_x, int begin_y, bool avoid);
        bool createAxisSymmetry();
        bool SearchLocalOptimalCover(int KM_local_hight, int KM_local_width, int b_x, int b_y, bool av);
        // Функции для проверки роста в то или иное направление
        int VerLocalRight(int max_cover, int restriction, bool avoidant, int axis, int KM_width, int KM_hight);
        int VerLocalBottom(int max_cover, int restriction, bool avoidant, int axis, int KM_width, int KM_hight);
        int VerLocalLeft(int max_cover, int restriction, bool avoidant, int axis, int KM_width, int KM_hight);
        int VerLocalTop(int max_cover, int restriction, bool avoidant, int axis, int KM_width, int KM_hight);

        bool IncludIN(int x_temp, int y_temp, cover c);
        bool SearchAxles();
        bool DeleteRedundancy();
        bool DeleteCover(int index);
        bool NormalizedBasis();

        cover coverTemp;
        cover coverBest;
};

#endif // SEARCHCOATING_H
