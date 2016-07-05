#include "rrt.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RRT w;
    w.show();

    return a.exec();
}
