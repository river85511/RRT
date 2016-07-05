#include "rrt.h"
#include "ui_rrt.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include <QPalette>
#include <QImage>

RRT::RRT(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RRT)
{
    ui->setupUi(this);

}

void RRT::DisplayMap_Mat2Pixmap(cv::Mat mat)
{
    cv::Mat rgb;
    QImage img;

    if(mat.channels() == 1)     //Grey image
    {
        img = QImage((const uchar*)(mat.data),
                     mat.cols,mat.rows,
                     mat.cols*mat.channels(),
                     QImage::Format_Indexed8);

    }else if(mat.channels() == 3)     // RGB image
    {
        cv::cvtColor(mat,rgb,CV_BGR2RGB);
        img = QImage((const uchar*)(rgb.data),
                     rgb.cols,rgb.rows,
                     rgb.cols*rgb.channels(),
                     QImage::Format_RGB888);
    }

    int w = ui->MapDislplay->width();
    int h = ui->MapDislplay->height();

    ui->MapDislplay->setPixmap(QPixmap::fromImage(img).scaled(w,h,Qt::KeepAspectRatio));
    ui->MapDislplay->show();
}

RRT::~RRT()
{
    delete ui;
}



void RRT::on_LoadButton_clicked()
{
    QString FilePath = QFileDialog::getOpenFileName(this, "Open Image", ".", "Image Files(*.jpg *.png)");
    cv::Mat img_ori;

    if(FilePath.length() == 0){
        //QMessageBox::information(NULL, "Warning", "Please select an image file!","はい");
    }else{

        img_ori = cv::imread(FilePath.toStdString()); // load image by openCV

        if(img_ori.empty()){
            QMessageBox::information(NULL, "Warning", "Image can't be read","はい");
        }else
            ui->LoadDisplay->setText(" Image Path = " + FilePath);
            cv::cvtColor(img_ori,this->rrt_map,CV_BGR2GRAY);
            this->DisplayMap_Mat2Pixmap(this->rrt_map);

    }



}
