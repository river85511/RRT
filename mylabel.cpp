#include "mylabel.h"

myLabel::myLabel(QWidget *parent):
    QLabel(parent)
{

}

void myLabel::mousePressEvent(QMouseEvent *event)
{
    this->x = event->x();
    this->y = event->y();

    if(event->button() == Qt::LeftButton){
        this->leftOrRight = 1;
    }else if(event->button() == Qt::RightButton){
        this->leftOrRight = 0;
    }

    emit mousePressed(this->x,this->y,this->leftOrRight);
}
