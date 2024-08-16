#include "interface.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>
void Interface::iniUI()
{
    bestScores = new QTextBrowser();
    nowScores = new QTextBrowser();
    bestScores->setText("最高分数："+QString::number(0));
    nowScores->setText("当前分数："+QString::number(0));
    nowScores->setMaximumSize(140,40);
    bestScores->setMaximumSize(140,40);
    nowScores->setStyleSheet("background-color: lightyellow;");
    bestScores->setStyleSheet("background-color: lightyellow;");
    QHBoxLayout *HLay1 = new QHBoxLayout();
    HLay1->addWidget(bestScores);
    HLay1->addWidget(nowScores);

    gameBox = new QWidget();
    gameBox->setFixedSize(boxLength,boxLength);
    gameBox->setStyleSheet("background-color: yellow;");
    QHBoxLayout *HLay2 = new QHBoxLayout();
    HLay2->addWidget(gameBox);

    /*test*/
    // QRect geometry = gameBox->geometry();
    // int x = geometry.x();
    // int y = geometry.y();
    // int width = geometry.width();
    // int height = geometry.height();

    // qDebug() << "Position:" << x << y;
    // qDebug() << "Size:" << width << height;
    // cubes = new Cube();
    // cubes->setParent(gameBox);
    // cubes->move(75,75);
    /**/
    // creatCube();

    btnRevocate = new QPushButton("撤回");
    btnReset = new QPushButton("重置");
    btnClose = new QPushButton("退出");
    QHBoxLayout *HLay3 = new QHBoxLayout();
    HLay3->addStretch();
    HLay3->addWidget(btnRevocate);
    HLay3->addWidget(btnReset);
    HLay3->addStretch();
    HLay3->addWidget(btnClose);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(HLay1);
    mainLayout->addLayout(HLay2);
    mainLayout->addLayout(HLay3);
    // mainLayout->addWidget(cubes);
    setLayout(mainLayout);
    adjustSize();

}

void Interface::iniSignalSlots()
{
    connect(btnClose,SIGNAL(clicked()),this,SLOT(close()));
}
bool Interface::isPositionFull(int m,int n)
{
    if(cube_positions[m][n]!=nullptr)
        return false;
    else
        return true;
}

void Interface::creatCube()
{
    static int m = std::rand()%CubesNum;//生成0-3范围的随机数
    static int n = std::rand()%CubesNum;
    while(!isPositionFull(m,n))
    {
        int temp_cnt=0;
        m=std::rand()%CubesNum;
        n=std::rand()%CubesNum;

        //检查游戏格子，是否全部占满
        for(int i=0;i<CubesNum;i++)
        {
            for(int j=0;j<CubesNum;j++)
            {
                if(!isPositionFull(i,j)) temp_cnt++;
            }
        }
        if(++this->theCubes != temp_cnt)
            qDebug()<<"WARN:计数错误 "<<temp_cnt+1<<" "<<this->theCubes+1;
        else
             qDebug()<<"现存方块 "<<temp_cnt+1<<" "<<this->theCubes+1;
        if(temp_cnt>=16)
        {
            game_flag = false;
            qDebug()<<"game over";
            break;
        }
    }

    cube_positions[m][n] = new Cube(nullptr,boxLength/CubesNum);
    cube_positions[m][n]->setParent(gameBox);
    QPoint point = QPoint(n*boxLength/CubesNum,
                          m*boxLength/CubesNum);
    int x = std::rand()%2+1;
    cube_positions[m][n]->update(std::exp2(x),point);
    cube_positions[m][n]->moveToPosition(point);
    cube_positions[m][n]->show();

    // qDebug()<<"生成一个方块，位于："<<m<<"x"<<n;
    // for(int i=0;i<CubesNum;i++)
    // {
    //     for(int j=0;j<CubesNum;j++)
    //     {
    //         if(cube_positions[i][j]!=nullptr)
    //         {
    //             qDebug()<<"在 "<<i<<"x"<<j<<" 处有方块";
    //         }
    //     }
    // }
}


//删除cube,指针指向null
void Interface::deleteCube(Cube *&p)
{
    if (p) {
        p->deleteLater();
        p = nullptr;  // 将传入的指针设为nullptr
        this->theCubes--;  // 更新方块计数
    }
}

void Interface::moveCube(int direction, Cube *& _cube)
{
    // 检查指针是否为 nullptr
    if(_cube == nullptr)
        return; // 如果 _cube 为空指针，直接返回，不执行后续操作

    int m, n;
    QPoint point;
    int length = boxLength / CubesNum;

    switch (direction) {
    case Move_direction::up:
        // m行号，对应point.y/L；n列号,对应point.x/L
        m = _cube->coord.y() / length;
        n = _cube->coord.x() / length;
        // static int up_step = 0; // 记录方块要到的行位置
        move_step=0;
        for(int i = m - 1; i >= 0; i--) {
            if(isPositionFull(i, n)) {
                move_step = i;
            }
            else {
                // 上方方块非空，且数字相同，合并
                if(_cube->num == cube_positions[i][n]->num
                    && cube_positions[i][n]!=nullptr)
                {
                    qDebug()<<"第"<<i<<"行为"<<cube_positions[i][n]->num<<",合并！";
                    point = QPoint(n * length, i * length);
                    _cube->animaMove(_cube->coord, point);
                    // 合并方块并更新数值
                    cube_positions[i][n]->update(
                        cube_positions[i][n]->num * 2,
                        cube_positions[i][n]->coord
                        );
                    move_step = m;

                    // 删除当前方块
                    deleteCube(_cube);
                    return; // 删除方块后直接返回，避免后续访问已删除的指针
                } else {
                    // 上方非空，且数字不同，则方块上移到非空方块的下一格
                    move_step = i + 1;
                    break;
                }
            }
        }

        // 如果方块上方有空格，则上移位
        if(move_step < m) {
            if(cube_positions[move_step][n]==nullptr)
            {
                point = QPoint(n * length, move_step * length);
                _cube->animaMove(_cube->coord, point);
                _cube->update(_cube->num, point);
                // 更新二维数组
                cube_positions[move_step][n] = _cube;
                // 将当前方块指针置为 nullptr，以防止进一步操作
                qDebug()<<_cube->num<<"向上移动到："<<move_step<<"行";
                _cube = nullptr;
            }
        }
        break;

    case Move_direction::down:
        // m行号，对应point.y/L；n列号,对应point.x/L
        m = _cube->coord.y() / length;
        n = _cube->coord.x() / length;
        // static int up_step = 0; // 记录方块要到的行位置
        move_step=0;
        for(int i = m + 1; i < CubesNum; i++) {
            if(isPositionFull(i, n)) {
                move_step = i; // 更新移动到的目标行
            } else {
                if(_cube->num == cube_positions[i][n]->num
                    && cube_positions[i][n] != nullptr)
                {
                    // qDebug() << "第" << i << "行为" << cube_positions[i][n]->num << ", 合并！";
                    point = QPoint(n * length, i * length);
                    _cube->animaMove(_cube->coord, point);

                    // 合并方块并更新数值
                    cube_positions[i][n]->update(cube_positions[i][n]->num * 2,
                                                 cube_positions[i][n]->coord);
                    move_step = m;

                    // 删除当前方块并返回，避免后续操作
                    deleteCube(_cube);
                    return;
                } else {
                    move_step = i - 1; // 如果不能合并，则移动到非空方块的上一行
                    break; // 下方已经无法继续移动，退出循环
                }
            }
        }

        // 如果方块下方有空格，则下移方块
        if(move_step > m) {
            if(cube_positions[move_step][n] == nullptr) {
                point = QPoint(n * length, move_step * length);
                _cube->animaMove(_cube->coord, point);
                _cube->update(_cube->num, point);

                // 更新二维数组
                cube_positions[move_step][n] = _cube;
                // 将当前方块指针置为 nullptr，以防止进一步操作
                _cube = nullptr;
            }
        }
        break;
    case Move_direction::left:
        // m行号，对应point.y/L；n列号,对应point.x/L
        m = _cube->coord.y() / length;
        n = _cube->coord.x() / length;
        // static int up_step = 0; // 记录方块要到的行位置
        move_step=0;
        for(int i = n - 1; i >= 0; i--) {
            if(isPositionFull(m, i)) {
                move_step = i;
            }
            else {
                // 左方方块非空，且数字相同，合并
                if(_cube->num == cube_positions[m][i]->num
                    && cube_positions[m][i]!=nullptr)
                {
                    point = QPoint(i * length, m * length);
                    _cube->animaMove(_cube->coord, point);
                    // 合并方块并更新数值
                    cube_positions[m][i]->update(
                        cube_positions[m][i]->num * 2,
                        cube_positions[m][i]->coord
                        );
                    move_step = n;

                    // 删除当前方块
                    deleteCube(_cube);
                    return; // 删除方块后直接返回，避免后续访问已删除的指针
                } else {
                    // left非空，且数字不同，则方块l移到非空方块的l一格
                    move_step = i + 1;
                    break;
                }
            }
        }

        // 如果方块上方有空格，则上移位
        if(move_step < n) {
            if(cube_positions[m][move_step]==nullptr)
            {
                point = QPoint(move_step * length, m * length);
                _cube->animaMove(_cube->coord, point);
                _cube->update(_cube->num, point);
                // 更新二维数组
                cube_positions[m][move_step] = _cube;
                // 将当前方块指针置为 nullptr，以防止进一步操作
                _cube = nullptr;
            }
        }
        break;
    case Move_direction::right:
        // m行号，对应point.y/L；n列号,对应point.x/L
        m = _cube->coord.y() / length;
        n = _cube->coord.x() / length;
        // static int up_step = 0; // 记录方块要到的行位置
        move_step=0;
        for(int i = n + 1; i < CubesNum; i++) {
            if(isPositionFull(m, i)) {
                move_step = i; // 更新移动到的目标行
            } else {
                if(_cube->num == cube_positions[m][i]->num
                    && cube_positions[m][i] != nullptr)
                {
                    point = QPoint(i * length, m * length);
                    _cube->animaMove(_cube->coord, point);

                    // 合并方块并更新数值
                    cube_positions[m][i]->update(cube_positions[m][i]->num * 2,
                                                 cube_positions[m][i]->coord);
                    move_step = n;

                    // 删除当前方块并返回，避免后续操作
                    deleteCube(_cube);
                    return;
                } else {
                    move_step = i - 1;
                    break;
                }
            }
        }

        if(move_step > n) {
            if(cube_positions[m][move_step] == nullptr) {
                point = QPoint(move_step * length, m * length);
                _cube->animaMove(_cube->coord, point);
                _cube->update(_cube->num, point);

                // 更新二维数组
                cube_positions[m][move_step] = _cube;
                // 将当前方块指针置为 nullptr，以防止进一步操作
                _cube = nullptr;
            }
        }
        break;
    default:
        break;
    }
}

void Interface::keyPressEvent(QKeyEvent *event)
{
    // 仅在非自动重复时处理按键事件
    if (!event->isAutoRepeat()) {
        switch (event->key()) {
        case Qt::Key_A:
            qDebug() << "A 键被按下";
            for(int i=1;i<CubesNum;i++)
            {
                for(int j=0;j<CubesNum;j++)
                {
                    if(cube_positions[j][i]!=nullptr)
                        moveCube(Move_direction::left,cube_positions[j][i]);
                }
            }
            creatCube();
            break;
        case Qt::Key_W:
            qDebug() << "W 键被按下";
            for(int i=1;i<CubesNum;i++)
            {
                for(int j=0;j<CubesNum;j++)
                {
                    if(cube_positions[i][j]!=nullptr)
                        moveCube(Move_direction::up,cube_positions[i][j]);
                }
            }
            creatCube();
            break;
        case Qt::Key_S:
            qDebug() << "S 键被按下";
            for(int i=CubesNum-2;i>=0;i--)
            {
                for(int j=0;j<CubesNum;j++)
                {
                    if(cube_positions[i][j]!=nullptr)
                        moveCube(Move_direction::down,cube_positions[i][j]);
                }
            }
            creatCube();
            break;
        case Qt::Key_D:
            qDebug() << "D 键被按下";
            for(int i=CubesNum-2;i>=0;i--)
            {
                for(int j=0;j<CubesNum;j++)
                {
                    if(cube_positions[j][i]!=nullptr)
                        moveCube(Move_direction::right,cube_positions[j][i]);
                }
            }
            creatCube();
            break;
        default:
            QWidget::keyPressEvent(event); // 传递未处理的按键事件
        }
    }
}


Interface::Interface(QWidget *parent) : QWidget(parent)
{
    iniUI();
    iniSignalSlots();
    setWindowTitle("2048");

    //分配空间
    cube_positions = new Cube **[CubesNum];//指向行
    for(int i=0;i<CubesNum;i++)//为每行分配空间
    {
        cube_positions[i] = new Cube *[CubesNum];
    }
    //初始化分配的空间
    for(int i=0;i<CubesNum;i++)
    {
        for(int j=0;j<CubesNum;j++)
        {
            cube_positions[i][j] = nullptr;
        }
    }
    // for(int i=0;i<CubesNum;i++)
    // {
    //     for(int j=0;j<CubesNum;j++)
    //     {
    //         if(cube_positions[i][j]!=nullptr)
    //         {
    //             qDebug()<<"在 "<<i<<"x"<<j<<" 处有方块";
    //         }
    //     }
    // }
}

Interface::~Interface()
{
    // delete cubes[0];
    for(int i=0;i<CubesNum;i++)
    {
        delete [] cube_positions[i];
    }
    delete [] cube_positions;
}
