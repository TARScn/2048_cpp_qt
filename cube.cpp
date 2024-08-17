#include "cube.h"
#include <QDebug>

Cube::Cube(QTextBrowser *parent, int n) : QTextBrowser(parent), num(2), coord(QPoint(0, 0))
{
    animation = new QPropertyAnimation(this, "pos");
    animation->setDuration(200); // Animation duration
    animation->setEasingCurve(QEasingCurve::Linear); // Animation effect

    setColor();
    this->setMaximumSize(n, n);
}

Cube::~Cube()
{
    delete animation; // Clean up animation
}

void Cube::update(int n, QPoint &co)
{
    num = n;
    coord = co;
    setColor();

    int num_font;
    if (n < 100)
        num_font = 30;
    else if (n < 1000)
        num_font = 24;
    else
        num_font = 16;

    setCubeNum(num_font);
}

void Cube::moveToPosition(QPoint &co)
{
    this->move(co.x(), co.y());
}

void Cube::animaMove(QPoint &co1, QPoint &co2)
{
    animation->setStartValue(co1); // Animation start position
    animation->setEndValue(co2); // Animation end position
    animation->start();
}
