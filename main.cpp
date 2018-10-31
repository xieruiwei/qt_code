#include <iostream>
#include<opencv2/opencv.hpp>
#include<cv.h>
using namespace cv;
using namespace std;
int main()
{
    Mat img1,img2,mask;
    img1=imread("F:\\QT_code\\LiuWenguo_homework\\task2_2\\lena.jpg");

    //获取图片1大小
    int height1 = img1.size().height;
    int width1 = img1.size().width;

    mask = Mat::zeros(img1.size(), CV_8UC1); //%二值模板，方便最後的合成

    img2=imread("F:\\QT_code\\LiuWenguo_homework\\task2_2\\pai.jpg");
    //获取图片2大小
    int height2 = img1.size().height;
    int width2 = img1.size().width;

    imshow("lena",img1);
    imshow("pai",img2);

    int a[4][4] = ginput();
    waitKey(3000);

//    [h1 w1]=size(img1);
//    mask=uint8(ones(h1,w1));    %二值模板，方便最後的合成

//    img2=imread('pai.jpg');
//    [h2 w2]=size(img2);

//    imshow(img1);
//    figure;imshow(img2);

//    p1=[1,1;w1,1;1,h1;w1,h1];
//    p2=ginput();        %依次點擊公告牌左上、右上、左下、右下

//    T=calc_homography(p1,p2);   %計算單應性矩陣
//    T=maketform('projective',T);   %投影矩陣

//    [imgn X Y]=imtransform(img1,T);     %投影
//    mask=imtransform(mask,T);

//    T2=eye(3);
//    if X(1)>0, T2(3,1)= X(1); end
//    if Y(1)>0, T2(3,2)= Y(1); end
//    T2=maketform('affine',T2);      %仿射矩陣

//    imgn=imtransform(imgn,T2,'XData',[1 w2],'YData',[1 h2]);    %仿射
//    mask=imtransform(mask,T2,'XData',[1 w2],'YData',[1 h2]);

//    img=img2.*(1-mask)+imgn.*mask;  %合成
//    figure;imshow(img,[])
    return 0;
}
