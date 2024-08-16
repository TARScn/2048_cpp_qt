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
#include <cstdlib>
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
    bool game_flag = true;//游戏结束标志
    int theCubes=0;//记录总方块
    bool keyHandled_A = false;  // 标志按键是否已被处理
    QPropertyAnimation *animation;
    QPushButton *btnRevocate;
    QPushButton *btnReset;
    QPushButton *btnClose;
    QTextBrowser *bestScores;
    QTextBrowser *nowScores;
    QWidget *gameBox;
    Cube **cubes2;
    Cube ***cube_positions;  //使用二维数组储存*Cube位置
    int _best_scores;
    int _now_scores;
    int move_step;
    void iniUI();            //UI创建与初始化
    void iniSignalSlots();   //初始化信号与槽的链接
    bool isPositionFull(int m,int n);
    void creatCube();
    void deleteCube(Cube *& p);
    void moveCube(int direction, Cube * &_cube);
private slots:


signals:
    void keyPressedSignal(int key);
protected:
    void keyPressEvent(QKeyEvent *event) override;

public:
    Interface(QWidget *parent = nullptr);
    ~Interface();
};


#endif // INTERFACE_H
