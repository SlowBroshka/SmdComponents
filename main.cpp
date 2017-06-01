#include <iostream>

#include <cv.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/types_c.h>
#include "Contour.h"
#include "HelpFunc.h"
#include "Line.h"
#include <ctime>

using namespace std;
using namespace cv;

int adkernel = 128;

cv::Mat src; cv::Mat src_gray, _src_gray, canny;

void adaptivethresh_callback(int, void* );

int main(int argc, char** argv ) {

    string filename = "/home/slowbro/Изображения/Elements/6.jpg";
    src = imread(filename, 1 );

    cvtColor( src, _src_gray, CV_BGR2GRAY );  //to binary

    //imwrite("/home/slowbro/Изображения/Elements/6Gray.jpg", _src_gray);

    blur( _src_gray, src_gray, BLUR_RANGE);   //add blur minimize

    /// Create Window
    string source_window = "Source";
    imshow( source_window, src_gray);

    createTrackbar(" AdBin", source_window, &adkernel, max_adkernel, adaptivethresh_callback);

    waitKey();

    return(0);
}
void adaptivethresh_callback(int, void* ){

    threshold(src_gray, src_gray, adkernel, 255, THRESH_BINARY_INV);
    imshow("1", src_gray);

    uint stime, ftime;

    stime = clock();
    double angle1 = getAngle1(src_gray);
    ftime = clock();
    cout<<"Try1: "<<angle1<<" Time: "<<ftime-stime<<endl;
    RotateShowImage("Try1", src, angle1);

//    stime = clock();
//    double angle2 = getAngle2(src_gray);
//    ftime = clock();
//    cout<<"Try2: "<<angle2<<" Time: "<<ftime-stime<<endl;
//    RotateShowImage("Try2", src, angle2);

//    stime = clock();
//    double angle3 = getAngle3(src_gray);
//    ftime = clock();
//    cout<<"Try3: "<<angle3<<" Time: "<<ftime-stime<<endl;
//    RotateShowImage("Try3", src, angle3);

    Mat interf;
    interf = DrawInterface(src, src_gray, angle1);
    imshow("DrawInterface", interf);
    imwrite("/home/slowbro/Изображения/Elements/6INTERF.jpg", interf);
}



