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
    gameBox->setFixedSize(length,length);
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
    /**/

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

void Interface::creatCube()
{

}

void Interface::deleteCube(Cube *p)
{
    p->deleteLater();
}

Interface::Interface(QWidget *parent) : QWidget(parent)
{
    iniUI();
    iniSignalSlots();
    setWindowTitle("2048");
}

Interface::~Interface()
{
    // delete cubes[0];
}
