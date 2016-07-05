#ifndef RRT_H
#define RRT_H

#include <QMainWindow>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include <QMouseEvent>

namespace Ui {
class RRT;
}

class RRT : public QMainWindow
{
    Q_OBJECT

public:
    explicit RRT(QWidget *parent = 0);
    void DisplayMap_Mat2Pixmap(cv::Mat mat);
    void mousePressEvent(QMouseEvent *event);
    ~RRT();

private slots:
    void on_LoadButton_clicked();

private:
    Ui::RRT *ui;

    cv::Mat rrt_map;

};

#endif // RRT_H
