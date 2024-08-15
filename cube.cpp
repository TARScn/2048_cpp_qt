#include "cube.h"

void Cube::update(int n, QPoint & co)
{
    num = n;
    coord = co;
    setColor();
}

Cube::Cube(QTextBrowser * parent, int n) : QTextBrowser(parent)
{
    num=2;
    coord = QPoint(0,0);
    setColor();
    this->setMaximumSize(n,n);
}

Cube::~Cube()
{

}
