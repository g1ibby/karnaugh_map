#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tabletrue.h"
#include "karnaughmap.h"
#include "searchcoating.h"
#include "gminifunction.h"
#include <QVector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    char BoolToChar(bool b);
    bool ColorTest(QColor c);
    QVector< QColor > arrayColor;
};

#endif // MAINWINDOW_H
