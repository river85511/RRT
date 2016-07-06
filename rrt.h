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

    void on_resetButton_clicked();

    void on_startButton_clicked();

    void on_distanceInputBox_textChanged(const QString &arg1);

private:
    Ui::RRT *ui;

    cv::Mat img_load;    //img_load is used for saving the loaded image, so that the image can return to its original state after "reset()"
    cv::Mat rrt_map;    //rrt_map is used for displaying on the label
    cv::Mat rrt_map_gray; //rrt_map_gray is used for locating the postion of the boundary

    bool startchosed;   //startchosed is used to check if there's a start
    bool goalchosed;    //goalchosed is used to check if there's a goal

    bool mapinputted; //mapinputted is used to check if there's a map loaded
    bool disinputted; //disinputted is used to check if the maximum allowable distance is inputted

    int dis_limit;  //dis_limit is used to save the maximum allowable distance inputted by the user
};

#endif // RRT_H
