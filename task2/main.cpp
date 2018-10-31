#include<iostream>
#include<opencv2/opencv.hpp>
#include<cv.h>
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include<time.h>
#include <windows.h>
using namespace cv;
using namespace std;


void DrawTransRec(Mat mat, int x, int y, int width, int height, CvScalar color, double alpha);

void DrawTransRec(Mat mat, int x, int y, int width, int height, CvScalar color, double alpha)
{
    IplImage * img;
    *img= IplImage(mat);
    IplImage * rec = cvCreateImage(cvSize(width, height), img->depth, img->nChannels);
    //if(x>0&&y>0&&x<mat.cols&&y<mat.){
    cv::Rect roi = cv::Rect(x, y, width, height) & cv::Rect(0, 0, mat.cols, mat.rows);
    if (roi.area() != width*height)return;
    cvRectangle(rec, cvPoint(0, 0), cvPoint(width, height), color, -1);
    cvSetImageROI(img, cvRect(roi.x, roi.y, roi.width, roi.height));
    cvAddWeighted(img, alpha, rec, 1 - alpha, 0.0, img);
    cvResetImageROI(img);
    cvReleaseImage( &rec);
}

int main()
{

    Mat picture(500, 500, CV_8UC3, Scalar(255, 255, 255, 0.5));    //定义一个Mat变量，用于存储每一帧的图像 以及画画
    //stringname = "我的摄像头";
    //【1】从摄像头读入视频
    VideoCapture capture(0);//若测试摄像头有没有打开，/*
    if(!capture.isOpened()){
        cout<< "cannot open the camera.";
        cin.get();
        return -1;
    }

    Mat edges; //定义一个Mat变量，用于存储每一帧的图像
    //【2】循环显示每一帧

    int everytime;
    SYSTEMTIME st = {0};
    GetLocalTime(&st);
    everytime = st.wSecond*1000 + st.wMilliseconds;

    while(1){

        capture >> picture;  //读取当前帧
        if(picture.empty()){
            printf("--(!) No captured frame -- Break!");
            //break;
        }
        else{
            cvtColor(picture, edges, CV_BGR2GRAY);//彩色转换成灰度
            //                blur(edges, edges, Size(7, 7));//模糊化
            //                Canny(edges, edges, 0, 30, 3);//边缘化
        }

        //画圆
        int r = 50;//半径
        Point center = Point(350, 250);  //其中2改为-1 表示填充
        circle(picture, center, r, Scalar(123, 21, 32), 2,8,0);

        //画标记
        //目前支持六种标记
        //MARKER_TILTED_CROSS,MARKER_STAR, MARKER_DIAMOND, MARKER_SQUARE ,MARKER_TRIANGLE_UP, MARKER_TRIANGLE_DOWN
        drawMarker(picture, Point(350, 250), Scalar(0, 0, 255), MARKER_TILTED_CROSS);

        //获取系统时间
        SYSTEMTIME st = {0};
        GetLocalTime(&st);
        everytime = st.wSecond*1000 + st.wMilliseconds - everytime;
        //输入文字
        Point textPt(210, 50);
        String text = to_string(everytime);
        everytime = st.wSecond*1000 + st.wMilliseconds;
        int fontFace = FONT_HERSHEY_PLAIN;
        double fontScale = 2;
        int thickness = 2;
        putText(picture, text, textPt, fontFace, fontScale, Scalar(0, 111, 255), thickness);
        //getTextSize()返回一个指定字体以及大小的String所占的空间
        int baseline = 0;
        Size textSize = getTextSize(text, fontFace,fontScale, thickness, &baseline);
        rectangle(picture, Point(0, 0), Point(0, 0), Scalar(0, 255, 0, 1), 1);




        imshow("bbbb",picture);
        imshow("a", edges); //显示当前帧

        waitKey(1); //延时30ms
    }

    //    // 画箭头
    //    Point point1 = Point(0, 0);
    //    Point point2 = Point(100, 100);  // 2表示线宽  8 表示线型  0 暂时不清楚  0.1表示箭头的长度
    //    arrowedLine(picture, point1, point2, Scalar(0, 255, 0), 2,8,0,0.1);

    //    //画直线
    //    point1 = Point(0, 100);
    //    point2 = Point(100, 200); // 2表示线宽  8 表示线型
    //    line(picture, point1, point2, Scalar(0, 0, 255), 2, 8, 0);



    //    //画矩形
    //    Rect rec(300,300,150,150);
    //    rectangle(picture, rec, Scalar(123, 21, 32), 2, 8, 0);

    //    //clipLine的作用是剪切图像矩形区域内部的直线
    //    point1 = Point(250, 250);
    //    point2 = Point(450, 450);
    //    line(picture, point1, point2, Scalar(0, 255, 0), 2, 8, 0);
    //    clipLine(rec, point1, point2);
    //    line(picture, point1, point2, Scalar(0, 0, 255), 2, 8, 0);

    //    //输入文字
    //    Point textPt(210, 50);
    //    String text = "drawtext";
    //    int fontFace = FONT_HERSHEY_PLAIN;
    //    double fontScale = 2;
    //    int thickness = 2;
    //    putText(picture, text, textPt, fontFace, fontScale, Scalar(0, 111, 255), thickness);
    //    //getTextSize()返回一个指定字体以及大小的String所占的空间
    //    int baseline = 0;
    //    Size textSize = getTextSize(text, fontFace,fontScale, thickness, &baseline);
    //    rectangle(picture, Point(textPt.x, textPt.y - textSize.height), Point(textPt.x + textSize.width, textPt.y + thickness/2), Scalar(0, 255, 0, 1), 1);


    //    //画椭圆
    //    Size z(20, 50);//轴线长度，横着20，竖着50
    //    ellipse(picture, Point(50, 150), z, 20.0, 0.0, 300.0, Scalar(55, 123, 222), -1);
    //    //参数说明，axes表示轴，20.0表示整个椭圆旋转20度，从0开始画到300度
    //    //重载函数利用了RotatedRect,表示在一个旋转矩形里画最大椭圆
    //    RotatedRect box1(Point(150, 150), Size(40, 100), -20);//负的为逆时针
    //    ellipse(picture, box1, Scalar(122, 122, 122));
    //    vector<Point> pointstest;
    //    ellipse2Poly(Point(50, 150), z, 20.0, 0.0, 300.0, 1, pointstest);


    //    //画多边形
    //    Point points[2][20];
    //    points[0][0] = Point(300, 100);
    //    points[0][1] = Point(400, 100);
    //    points[0][2] = Point(450, 200);
    //    points[0][3] = Point(350, 250);
    //    points[0][4] = Point(250, 200);

    //    points[1][0] = Point(300, 100) + Point(-200, +150);
    //    points[1][1] = Point(400, 100) + Point(-200, +150);
    //    points[1][2] = Point(450, 200) + Point(-200, +150);
    //    points[1][3] = Point(350, 250) + Point(-200, +150);
    //    points[1][4] = Point(250, 200) + Point(-200, +150);
    //    const Point* pt[2] = { points[0], points[1] };
    //    int npt[2] = { 5,5 };
    //    polylines(picture, pt, npt, 2, 1, Scalar(0, 0, 255), 3);
    //    fillPoly(picture, pt, npt, 1, Scalar(250, 255, 0), 8);

    //绘制半透明矩形
    //   DrawTransRec(picture, 50, 320, 400, 100, Scalar(255, 122, 122), 0.2);


    return 0;

}
