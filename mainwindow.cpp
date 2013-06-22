#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

char MainWindow::BoolToChar(bool b)
{
    return b ? '1' : '0';
}

bool MainWindow::ColorTest(QColor c)
{
    for (int i = 0; i < arrayColor.size(); i++)
    {
        if (arrayColor[i] == c)
        {
            return true;
        }
    }
    return false;
}

void MainWindow::on_pushButton_3_clicked()
{
    // Построение по формуле таблицы истиности
    tableTrue tT;
    tT.CreateTable(ui->lineEdit->text());
    // Очистим таблицу
    ui->tableWidget->clear();
    //Задаём число столбцов
    ui->tableWidget->setColumnCount(tT.varible_num + 1);
    //Задаём число строк
    ui->tableWidget->setRowCount(pow(2, tT.varible_num) + 1);

    //Задаём ширину столбца
    ui->tableWidget->horizontalHeader()->setDefaultSectionSize(25);
    ui->tableWidget->verticalHeader()->setDefaultSectionSize(20);

    int sym = 0;
    for (int k = 0; k < 91; k++) {
            if (tT.varible[k] > 0) {
                char buf = k;
                ui->tableWidget->setItem(0,sym,new QTableWidgetItem(QChar(buf)));
                sym = sym + 1;
            }
    }
    ui->tableWidget->setItem(0, tT.varible_num, new QTableWidgetItem(QChar('F')));

    for (int i = 1; i < pow(2, tT.varible_num) + 1; i++) {
        for (int j = 0; j < tT.varible_num + 1; j++) {

            ui->tableWidget->setItem(i, j, new QTableWidgetItem(QChar(BoolToChar(tT.tableT[i - 1][j]))));
        }
    }

    // Построение по таблицы истиности карты карно

    karnaughMap kM;
    kM.createMap(tT.tableT, tT.varible_num);


    ui->tableWidget_2->clear();
    ui->tableWidget_2->setColumnCount(kM.size_k_m);
    ui->tableWidget_2->setRowCount(kM.size_k_n);

    //Задаём ширину столбца
    ui->tableWidget_2->horizontalHeader()->setDefaultSectionSize(25);
    ui->tableWidget_2->verticalHeader()->setDefaultSectionSize(20);

    for (int i = 0; i < kM.size_k_n; i++) {
          for (int j = 0; j < kM.size_k_m; j++) {
              ui->tableWidget_2->setItem(i, j, new QTableWidgetItem(QChar(BoolToChar(kM.karMap[i][j]))));
          }
    }

    // Запускаем поиск покрытий в карты карно
    searchCoating sC;
    sC.getCover(kM.karMap, kM.size_k_n, kM.size_k_m, 'D');



    // A+!B&(C+!B)
    QColor color_1 = QColor(0, 255, 0, 50);
    QColor color_2 = QColor(255, 0, 0, 30);

    QColor temp = ui->tableWidget_2->item(0, 0)->backgroundColor();

    for(int i = 0; i < sC.cover_size; i++) {
        QColor in_color = QColor(qrand() % 230, qrand() % 230, qrand() % 230, 50);
        while (ColorTest(in_color) == true)
        {
            in_color = QColor(qrand() % 230, qrand() % 230, qrand() % 230, 80);
        }
        arrayColor.push_back(in_color);
            for(int j = 0; j < sC.KM_cover[i].size; j++) {

                if (ui->tableWidget_2->item(sC.KM_cover[i].elements[j][0],sC.KM_cover[i].elements[j][1])->backgroundColor() == temp)
                {
                    ui->tableWidget_2->item(sC.KM_cover[i].elements[j][0],sC.KM_cover[i].elements[j][1])->setBackgroundColor(in_color);
                }
                else if (ui->tableWidget_2->item(sC.KM_cover[i].elements[j][0],sC.KM_cover[i].elements[j][1])->backgroundColor() != color_1)
                {
                    ui->tableWidget_2->item(sC.KM_cover[i].elements[j][0],sC.KM_cover[i].elements[j][1])->setBackgroundColor(color_2);
                }

            }
     }

    // По построинным покрытиям состовляем минимизрованную формулу
    gMiniFunction gM;
    string s = gM.getMiniFunc(sC.KM_cover, sC.cover_size, tT.varible, tT.varible_num, 'D', log(sC.KM_hight_global) / log(2) + log(sC.KM_width_global) / log(2));

    ui->lineEdit_2->setText(QString::fromStdString(s));

}
