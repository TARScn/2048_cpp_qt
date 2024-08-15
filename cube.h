#ifndef CUBE_H
#define CUBE_H
#include <QTextBrowser>
#include <QPoint>
class Cube:public QTextBrowser
{
    Q_OBJECT
private:
    QPoint coord;
    int num;
    enum color{lightblue=2,teal=4,blue=8,lightpink=16,
                 mediumorchid=32,pink=64,mediumseagreen=128,
                 purple=256,lightcyan=512,mediumpurple=1024,
                 red=2048};
    void setColor()
    {
        switch (this->num) {
        case color::lightblue:
            this->setStyleSheet("background-color: lightblue;");
            break;
        case color::teal:
            this->setStyleSheet("background-color: teal;");
            break;
        case color::blue:
            this->setStyleSheet("background-color: blue;");
            break;
        case color::lightpink:
            this->setStyleSheet("background-color: lightpink;");
            break;
        case color::mediumorchid:
            this->setStyleSheet("background-color: mediumorchid;");
            break;
        case color::pink:
            this->setStyleSheet("background-color: pink;");
            break;
        case color::mediumpurple:
            this->setStyleSheet("background-color: mediumpurple;");
            break;
        case color::purple:
            this->setStyleSheet("background-color: purple;");
            break;
        case color::lightcyan:
            this->setStyleSheet("background-color: lightcyan;");
            break;
        case color::mediumseagreen:
            this->setStyleSheet("background-color: mediumseagreen;");
            break;
        default:
            this->setStyleSheet("background-color: red;");
            break;
        }
    }
public:
    Cube(QTextBrowser * parent = nullptr, int n=75);
    ~Cube();
    void update(int n, QPoint & co);
};

#endif // CUBE_H
