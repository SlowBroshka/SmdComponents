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

    uint stime = clock();

    /// Create Window
    string source_window = "Source";
    imshow( source_window, src );

    createTrackbar(" AdBin", source_window, &adkernel, max_adkernel, adaptivethresh_callback);

    waitKey();

    return(0);
}
void adaptivethresh_callback(int, void* ){

    threshold(_src_gray, src_gray, adkernel, 255, THRESH_BINARY_INV);


    double angle1 = GetOutPutAngle(src_gray);
    cout<<"Try1: "<<angle1<<endl;
    RotateShowImage("Try1", src, angle1);


    double angle2 = GetOutPutAngle2(src_gray);
    cout<<"Try2: "<<angle2<<endl;
    RotateShowImage("Try2", src, angle2);

    double angle3 = GetOutPutAngel3(src_gray);
    cout<<"Try3: "<<angle3<<endl;
    RotateShowImage("Try3", src, angle3);

    Mat interf;
    interf = DrawInterface(src, src_gray, angle3);
    imshow("DrawInterface", interf);
    imwrite("/home/slowbro/Изображения/Elements/6INTERF.jpg", interf);
}



