#ifndef INTERFACE_H
#define INTERFACE_H
#include <QWidget>
#include <QFrame>
#include <QPushButton>
#include <QTextBrowser>
#include <QString>
#include <QPoint>
#include "cube.h"

class Interface:public QWidget
{
    Q_OBJECT
private:
    static const int Cubes=4;
    static const int length=300;
    QPushButton *btnRevocate;
    QPushButton *btnReset;
    QPushButton *btnClose;
    QTextBrowser *bestScores;
    QTextBrowser *nowScores;
    QWidget *gameBox;
    Cube *cubes;
    int cube_positions[Cubes][Cubes];
    int _best_scores;
    int _now_scores;
    void iniUI();            //UI创建与初始化
    void iniSignalSlots();   //初始化信号与槽的链接
    void creatCube();
    void deleteCube(Cube *p);
private slots:
               // void do_start();
public:
    Interface(QWidget *parent = nullptr);
    ~Interface();
};


#endif // INTERFACE_H
