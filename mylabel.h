#ifndef MYLABEL_H
#define MYLABEL_H

#include <QWidget>
#include <QLabel>
#include <QMouseEvent>

class myLabel : public QLabel
{
    Q_OBJECT
public:
    explicit myLabel(QWidget *parent = 0);

    void mousePressEvent(QMouseEvent *event);

signals:
    void mousePressed(int x, int y, bool leftOrRight);

public slots:

private:
    int x,y;
    bool leftOrRight;
};

#endif // MYLABEL_H
