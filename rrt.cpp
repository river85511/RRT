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


RRT::RRT(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RRT)
{
    ui->setupUi(this);
    this->setWindowTitle("Rapidly Exploring Random Trees (RRT)");

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

    //int w = ui->MapDislplay->width();
    //int h = ui->MapDislplay->height();

    //ui->MapDislplay->setPixmap(QPixmap::fromImage(img).scaled(w,h,Qt::KeepAspectRatio));

    ui->MapDislplay->setPixmap(QPixmap::fromImage(img));
    ui->MapDislplay->show();

}

void RRT::mousePressEvent(QMouseEvent *event)
{
    QPoint mappedPos = ui->MapDislplay->mapFromGlobal(QCursor::pos());
    if( (mappedPos.x()>0) && (mappedPos.x()<ui->MapDislplay->width()) &&   //0<x<width
        (mappedPos.y()>0  && mappedPos.y()<ui->MapDislplay->height()))     //0<y<height
    {
        qDebug() << mappedPos ;

        cv::Point p = cv::Point(mappedPos.x(),mappedPos.y());

        cv::circle(rrt_map,p,1,cv::Scalar(0,255,0),5,8);
        DisplayMap_Mat2Pixmap(rrt_map);
    }
}


RRT::~RRT()
{
    delete ui;
}



void RRT::on_LoadButton_clicked()
{
    //圖得<= 800x500 pixels

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


            cv::resize(img_ori,img_ori,cv::Size(800,500));
            cv::cvtColor(img_ori,this->rrt_map,CV_BGR2GRAY);
            this->DisplayMap_Mat2Pixmap(this->rrt_map);

    }

}
