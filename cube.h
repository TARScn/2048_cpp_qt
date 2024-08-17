#ifndef CUBE_H
#define CUBE_H

#include <QTextBrowser>
#include <QPropertyAnimation>
#include <QString>
#include <QPoint>

class Cube : public QTextBrowser
{
    Q_OBJECT

private:
    QPropertyAnimation *animation;

    enum color {
        lightblue = 2,
        teal = 4,
        blue = 8,
        lightgreen = 16,
        mediumorchid = 32,
        pink = 64,
        mediumseagreen = 128,
        purple = 256,
        lightcyan = 512,
        mediumpurple = 1024,
        red = 2048
    };

    void setColor()
    {
        QString colorStyle;
        switch (this->num) {
        case color::lightblue:
            colorStyle = "background-color: lightblue;";
            break;
        case color::teal:
            colorStyle = "background-color: teal;";
            break;
        case color::blue:
            colorStyle = "background-color: blue;";
            break;
        case color::lightgreen:
            colorStyle = "background-color: lightgreen;";
            break;
        case color::mediumorchid:
            colorStyle = "background-color: mediumorchid;";
            break;
        case color::pink:
            colorStyle = "background-color: pink;";
            break;
        case color::mediumpurple:
            colorStyle = "background-color: mediumpurple;";
            break;
        case color::purple:
            colorStyle = "background-color: purple;";
            break;
        case color::lightcyan:
            colorStyle = "background-color: lightcyan;";
            break;
        case color::mediumseagreen:
            colorStyle = "background-color: mediumseagreen;";
            break;
        default:
            colorStyle = "background-color: red;";
            break;
        }
        this->setStyleSheet(colorStyle);
    }

    void setCubeNum(int num_font)
    {
        this->setText(QString::number(num));
        QTextCursor cursor = this->textCursor();
        cursor.select(QTextCursor::Document); // Select entire text
        QTextCharFormat charFormat;
        charFormat.setFontPointSize(num_font);   // Set font size
        charFormat.setFontWeight(QFont::Bold); // Set font weight to bold
        QTextBlockFormat blockFormat;
        blockFormat.setAlignment(Qt::AlignCenter); // Set text alignment to center
        cursor.setCharFormat(charFormat); // Apply character format
        cursor.mergeBlockFormat(blockFormat); // Apply block format
    }

public:
    QPoint coord;
    int num;

    Cube(QTextBrowser *parent = nullptr, int n = 70);
    ~Cube();
    void update(int n, QPoint &co);
    void moveToPosition(QPoint &co);
    void animaMove(QPoint &co1, QPoint &co2);
};

#endif // CUBE_H
