#ifndef INTERFACE_H
#define INTERFACE_H
#include <QWidget>
#include <QFrame>
#include <QPushButton>
#include <QTextBrowser>
#include <QString>
#include <QPoint>
#include <QKeyEvent>
#include <QPropertyAnimation>
#include <QTimer>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cmath>
#include "cube.h"

class Interface:public QWidget
{
    Q_OBJECT
private:
    static const int CubesNum=4;
    static const int boxLength=300;
    enum Key_NUM{W=87,A=65,S=83,D=68};
    enum Move_direction{up,down,right,left};
    bool gameover_flag = false;//游戏结束标志
    int theCubes=0;//记录总方块

    QPropertyAnimation *animation;
    QPushButton *btnSave;
    QPushButton *btnReset;
    QPushButton *btnClose;
    QTextBrowser *bestScores;
    QTextBrowser *nowScores;
    QWidget *gameBox;
    QTimer *timer;
    Cube ***cube_positions;  //使用二维数组储存*Cube位置
    int _best_scores=0;
    int _now_scores=0;
    int move_step;
    void iniUI();            //UI创建与初始化
    void iniSignalSlots();   //初始化信号与槽的链接
    bool isPositionFull(int m,int n);
    void creatCube();
    void deleteCube(Cube *& p);
    void moveCube(int direction, Cube * &_cube);
    void scoresUpdate(int addscores);
    bool isGameOver();
    void loadScores();
    void loadGameBox();
private slots:
    void gameRestart();
    void onTimeout();
    void saveGameBox();
    void noSaveGameBox();
    void saveGameScores();
signals:
    void keyPressedSignal(int key);
protected:
    void keyPressEvent(QKeyEvent *event) override;

public:
    Interface(QWidget *parent = nullptr);
    ~Interface();
};


#endif // INTERFACE_H
