#include "rrt.h"
#include "ui_rrt.h"

#include <iostream>
#include <ctime>

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
    this->mapinputted = 0;
    this->disinputted = 0;

    goalfound = 0;

    connect(ui->MapDislplay,SIGNAL(mousePressed(int,int,bool)),this,SLOT(mousePressed(int,int,bool)));

}

RRT::~RRT()
{
    delete ui;
}



void RRT::DisplayMap_Mat2Pixmap(const cv::Mat& mat)
{
    cv::Mat rgb;
    QImage img;

    if(mat.channels() == 1)     //Gray image
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

void RRT::solve()
{

    srand(time(NULL));

    cv::Point start = cv::Point(startPoint_x,startPoint_y);
    cv::Point goal = cv::Point(goalPoint_x,goalPoint_y);

    goalfound = 0;

    clock_t t1, t2;
    t1 = clock();
    while(goalfound == 0)/*for(int i =0; i< 50; i++)*/{

        this->rand_x = rand()% 800;
        this->rand_y = rand()% 500;

        if(checkDotInBoundary(rand_x,rand_y)){

            cv::Point randPoint = cv::Point(rand_x,rand_y);
            int closestNode_num = findClosestDot(randPoint);

            if(DistanceBetweeenDots(closestNode_num,randPoint) <= dis_limit)
            {

                cv::Point closestNode = cv::Point(mytree[closestNode_num].getX(),mytree[closestNode_num].getY());

                if(checkLineInBoundary(closestNode,randPoint))
                {
                    Node* newNode = new Node(randPoint.x,randPoint.y,closestNode_num);
                    mytree.push_back(*newNode);

                    int currentNode_num = mytree.size()-1;

                            if(DistanceBetweeenDots(currentNode_num,goal) <= dis_limit)
                            {

                                if(checkLineInBoundary(randPoint,goal))
                                {
                                    Node* goalNode = new Node(goal.x,goal.y,currentNode_num);
                                    mytree.push_back(*goalNode);

                                    findMainRoot();
                                    goalfound = 1;
                                }
                            }

                }

            }else
            {
                //qDebug() << "Too Far!" ;
                cv::Point arranged_randPoint =  extendWithinDistanceLimit(closestNode_num,randPoint);

                cv::Point closestNode = cv::Point(mytree[closestNode_num].getX(),mytree[closestNode_num].getY());

                if(checkLineInBoundary(closestNode,arranged_randPoint))
                {

                        Node* newNode = new Node(arranged_randPoint.x,arranged_randPoint.y,closestNode_num);
                        mytree.push_back(*newNode);

                        int currentNode_num = mytree.size()-1;

                        if(DistanceBetweeenDots(currentNode_num,goal) <= dis_limit)
                        {
                                if(checkLineInBoundary(arranged_randPoint,goal))
                                {
                                    Node* goalNode = new Node(goal.x,goal.y,currentNode_num);
                                    mytree.push_back(*goalNode);

                                    findMainRoot();
                                    goalfound = 1;
                                }

                        }

                }

            }


        }

    }
    t2 = clock();
    QString str = QString("%Processing time = lf\n").arg((t2-t1)/(double)(CLOCKS_PER_SEC));
    qDebug() << str;


}

bool RRT::checkDotInBoundary(const int& x,const int& y)
{
    if(rrt_map_gray.at<uchar>(y,x) == 255)  return true;
    else return false;
}

bool RRT::checkLineInBoundary(const cv::Point& a, const cv::Point& b)
{
    cv::LineIterator it(this->rrt_map_gray,a,b,8);
    vector<cv::Vec3b> buf(it.count);
    for(int i=0; i <it.count; i++, ++it){
        buf[i] = (const cv::Vec3b)*it;
        if(buf[i] == cv::Vec3b(0,0,0))
            return false;
    }

    return true;
}

int RRT::findClosestDot(const cv::Point& a)
{
    int distance;
    int min_distance;
    int node_num;

    for(int i = 0; i < mytree.size(); i++){
        int dx = (a.x - mytree[i].getX());
        int dy = (a.y - mytree[i].getY());
        distance = dx*dx + dy*dy;

        if(i == 0){
            min_distance = distance;
            node_num = i;
        }

        if(distance < min_distance){
            min_distance = distance;
            node_num = i;
        }
    }

    return node_num;

}

int RRT::DistanceBetweeenDots(const int& closestNode ,const cv::Point& a)
{
    int distance;

    int dx = (a.x - mytree[closestNode].getX());
    int dy = (a.y - mytree[closestNode].getY());
    distance = dx*dx + dy*dy;

    return distance;
}

cv::Point RRT::extendWithinDistanceLimit(const int& closestNode,const cv::Point& b)
{
    int start_x = mytree[closestNode].getX();
    int start_y = mytree[closestNode].getY();
    cv::Point start(start_x,start_y);
    cv::Point p;

    cv::LineIterator it(this->rrt_map_gray,start,b,8);
    p = cv::Point(it.pos().x,it.pos().y);
    for(int i=0; i <it.count; i++, ++it){

            if(DistanceBetweeenDots(closestNode,p) > dis_limit){
                break;
            }
            p = cv::Point(it.pos().x,it.pos().y);
    }

    return p;

}

void RRT::findMainRoot()
{
    int lastNode_num = mytree.size()-1;
    int parent = mytree[lastNode_num].getParent();

    int i = 0;

    Node* newNode = new Node(mytree[lastNode_num].getX(),mytree[lastNode_num].getY(),i);
    mainRoot.push_back(*newNode);
    i++;

    cv::Point goal = cv::Point(mytree[lastNode_num].getX(),mytree[lastNode_num].getY());
    cv::Point now;
    cv::Point last;

    while(true){

        Node* newNode = new Node(mytree[parent].getX(),mytree[parent].getY(),i);
        mainRoot.push_back(*newNode);

        now = cv::Point(mytree[parent].getX(),mytree[parent].getY());

        if(i == 1 ){
            cv::line(this->rrt_map,goal,now,cv::Scalar(0,0,0));
        }else{
            cv::line(this->rrt_map,last,now,cv::Scalar(0,0,0));
        }

        i++;
        qDebug() << parent;
        if(parent == 0){
            break;
        }
        cv::circle(this->rrt_map,cv::Point(mytree[parent].getX(),mytree[parent].getY()),1,cv::Scalar(255,160,160),5,8);
        last = cv::Point(mytree[parent].getX(),mytree[parent].getY());

        parent = mytree[parent].getParent();



    }

    DisplayMap_Mat2Pixmap(rrt_map);

}

void RRT::mousePressed(int x, int y,bool leftOrRight)
{

    if(mapinputted == 1){       //if then map is loaded then....

        if(this->startchosed ==0 || this->goalchosed == 0){     // if the user hasn't input starting point and goal point

            if(leftOrRight == 1 && this->startchosed == 0)    //Left Click for starting point
            {
                startPoint_x = x;
                startPoint_y = y;
                cv::circle(this->rrt_map,cv::Point(x,y),4,cv::Scalar(0,255,0),5,8);
                this->startchosed = 1;

                Node* startNode = new Node(x,y,0);
                mytree.push_back(*startNode);
            }
            else if(leftOrRight == 0 && goalchosed == 0)   //Right Click for goal
            {
                goalPoint_x = x;
                goalPoint_y = y;
                cv::circle(this->rrt_map,cv::Point(x,y),4,cv::Scalar(0,0,255),5,8);
                this->goalchosed = 1;
            }

            DisplayMap_Mat2Pixmap(this->rrt_map);       //Display the starting point and goal on the map!
        }

    }

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

        }else                                                                       // map is loaded correctly

            this->mapinputted = 1;

            ui->LoadDisplay->setText(" Image Path = " + FilePath);

            cv::resize(this->img_load,this->rrt_map,cv::Size(800,500));             //resize the image to 800x500 pixels
            this->DisplayMap_Mat2Pixmap(this->rrt_map);                             //display the map on label

            QMessageBox::information(NULL, "提醒", "Please select your starting point and goal!","はい");

            cv::cvtColor(this->rrt_map,this->rrt_map_gray,CV_BGR2GRAY);            //to locate the positions of the boundary
            this->startchosed = 0;                                                  //enable user to set a new starting point
            this->goalchosed = 0;                                                   //enable user to set a new goal

    }

}

void RRT::on_resetButton_clicked()
{
    if(mapinputted == 1){

        cv::resize(this->img_load,this->rrt_map,cv::Size(800,500));             //resize the image to 800x500 pixels
        this->DisplayMap_Mat2Pixmap(this->rrt_map);                             //display the map on label

        this->startchosed = 0;
        this->goalchosed = 0;
        startPoint_x = 0;
        startPoint_y = 0;
        goalPoint_x = 0;
        goalPoint_y = 0;

        goalfound = 0;

        mytree.clear();
        mainRoot.clear();

        if(disinputted == 1){
            ui->distanceInputBox->setText("");
            this->disinputted = 0;
        }

    }else if(mapinputted == 0){

        if(disinputted == 1){
            ui->distanceInputBox->setText("");
            this->disinputted = 0;
        }

        QMessageBox::information(NULL, "提醒", "Please load a map first!","はい");

    }
}

void RRT::on_startButton_clicked()
{
    if(mapinputted == 1){

        if(startchosed == 0 || goalchosed == 0 || disinputted ==0){

            if(startchosed == 0 || goalchosed == 0)
                QMessageBox::information(NULL, "提醒", "Please select your start and goal!","はい");

            if(disinputted ==0)
                QMessageBox::information(NULL, "提醒", "Please input maximum allowable distance!","はい");
        }
        else if(startchosed == 1 && goalchosed == 1 && disinputted == 1){
            qDebug() << "START!";

            //clock_t t1,t2;
            //t1 = clock();
            solve();
            //t2 = clock();

            //QString str = QString("%Processing time = lf\n").arg((t2-t1)/(double)(CLOCKS_PER_SEC));
            //qDebug() << str;

        }

    }else if(mapinputted == 0){
        QMessageBox::information(NULL, "提醒", "Please load a map first!","はい");
    }
}

void RRT::on_distanceInputBox_textChanged(const QString &arg1)
{
    if(arg1.length() != 0){
        this->dis_limit = arg1.toInt();
        this->dis_limit = (this->dis_limit)*(this->dis_limit);  //reduce the time to do square root
        this->disinputted = 1;
    }
}
