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
    ~RRT();

private slots:
    void on_LoadButton_clicked();
    void mousePressed(int x, int y,bool leftOrRight);

private:
    Ui::RRT *ui;

    cv::Mat img_load;    //img_load is used for saving the loaded image, so that the image can return to its original state after "reset()"
    cv::Mat rrt_map;    //rrt_map is used for displaying on the label
    cv::Mat rrt_map_gray; //rrt_map_gray is used for locating the postion of the boundary

    bool startchosed;
    bool goalchosed;
};

#endif // RRT_H
