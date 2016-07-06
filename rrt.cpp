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
#include <QPainter>
#include <QDebug>
#include <QPoint>
#include <QCursor>


#include <unistd.h>

RRT::RRT(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RRT)
{
    ui->setupUi(this);
    this->setWindowTitle("Rapidly Exploring Random Trees (RRT)");

    this->startchosed = 0;
    this->goalchosed = 0;

    connect(ui->MapDislplay,SIGNAL(mousePressed(int,int,bool)),this,SLOT(mousePressed(int,int,bool)));

}

RRT::~RRT()
{
    delete ui;
}


void RRT::on_LoadButton_clicked()
{
    //圖得<= 800x500 pixels

    QString FilePath = QFileDialog::getOpenFileName(this, "Open Image", ".", "Image Files(*.jpg *.png)");

    if(FilePath.length() == 0){
        //QMessageBox::information(NULL, "Warning", "Please select an image file!","はい");
    }else{

        this->img_load = cv::imread(FilePath.toStdString()); // load image by openCV

        if(this->img_load.empty()){
            QMessageBox::information(NULL, "Warning", "Image can't be read","はい");
        }else
            ui->LoadDisplay->setText(" Image Path = " + FilePath);


            cv::resize(this->img_load,this->rrt_map,cv::Size(800,500));             //resize the image to 800x500 pixels
            this->DisplayMap_Mat2Pixmap(this->rrt_map);                             //display the map on label

            QMessageBox::information(NULL, "提醒", "Please select your starting point and goal!","はい");

            cv::cvtColor(this->img_load,this->rrt_map_gray,CV_BGR2GRAY);            //to locate the positions of the boundary
            this->startchosed = 0;                                                  //enable user to set a new starting point
            this->goalchosed = 0;                                                   //enable user to set a new goal

    }

}

void RRT::DisplayMap_Mat2Pixmap(cv::Mat mat)
{
    cv::Mat rgb;
    QImage img;

    if(mat.channels() == 1)     //Gray image
    {
        qDebug() << "gray";
        img = QImage((const uchar*)(mat.data),
                     mat.cols,mat.rows,
                     mat.cols*mat.channels(),
                     QImage::Format_Indexed8);

    }else if(mat.channels() == 3)     // RGB image
    {
        qDebug() << "rgb";
        cv::cvtColor(mat,rgb,CV_BGR2RGB);
        img = QImage((const uchar*)(rgb.data),
                     rgb.cols,rgb.rows,
                     rgb.cols*rgb.channels(),
                     QImage::Format_RGB888);
    }

    //int w = ui->MapDislplay->width();
    //int h = ui->MapDislplay->height();
    //ui->MapDislplay->setPixmap(QPixmap::fromImage(img).scaled(w,h,Qt::KeepAspectRatio));

    ui->MapDislplay->setPixmap(QPixmap::fromImage(img));
    ui->MapDislplay->show();

}

void RRT::mousePressed(int x, int y,bool leftOrRight)
{

    //QString str = QString("x= %1 , y = %2").arg(x).arg(y);
    //qDebug() << str;
    if(this->startchosed ==0 || this->goalchosed == 0){
        cv::Point p = cv::Point(x,y);

        if(leftOrRight == 1 && this->startchosed == 0)    //Left  Click
        {
            cv::circle(this->rrt_map,p,1,cv::Scalar(0,255,0),5,8);
            this->startchosed = 1;
        }
        else if(leftOrRight == 0 && goalchosed == 0)   //Right Click
        {
            cv::circle(this->rrt_map,p,1,cv::Scalar(0,0,255),5,8);
            this->goalchosed = 1;
        }

        DisplayMap_Mat2Pixmap(this->rrt_map);
    }
}
