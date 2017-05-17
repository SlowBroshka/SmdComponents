#include <iostream>

#include <cv.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/types_c.h>

#include "Contour.h"
#include "HelpFunc.h"

using namespace std;
using namespace cv;

Mat src; Mat src_gray, _src_gray;
int thresh = 100;
int max_thresh = 255;
int adkernel = 128;
int max_adkernel = 255;

RNG rng(12345);


void thresh_callback(int, void* );

void adaptivethresh_callback(int, void* );

int main( int argc, char** argv ) {

    string filename = "/home/slowbro/Изображения/Elements/5.jpg";
    src = imread(filename, 1 );

    /// Convert image to gray and blur it
    cvtColor( src, _src_gray, CV_BGR2GRAY );
    blur( _src_gray, src_gray, Size(3,3) );

    /// Create Window
    char* source_window = "Source";
    namedWindow( source_window, CV_WINDOW_AUTOSIZE );
    imshow( source_window, src );

    createTrackbar(" AdBin", "Source", &adkernel, max_adkernel, adaptivethresh_callback);
    createTrackbar( " Canny thresh:", "Source", &thresh, max_thresh, thresh_callback );
    thresh_callback( 0, 0 );

    waitKey(0);
    return(0);
}


void adaptivethresh_callback(int, void* ){
    //Mat adgrey;
    threshold(_src_gray, src_gray, adkernel, 255, THRESH_BINARY_INV);

    imshow("adGray",src_gray);

}
void thresh_callback(int, void* )
{
    Mat canny_output;
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;

    /// Detect edges using canny
    Canny( src_gray, canny_output, thresh, thresh*2, 3 );
    /// Find contours
    findContours( src_gray, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

    /// Draw contours
    Mat drawing = Mat::zeros( src_gray.size(), CV_8UC3);
    for( int i = 0; i< contours.size(); i++ )
    {
        if (contours.size() >= 4 && contourArea(contours[i]) > 100) {
            Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
            drawContours(drawing, contours, i, color, 2, 8, hierarchy, 0, Point());
            cout << "№ " << i << " Points: " << contours[i].size() << endl;
            for (auto j = 0; j < contours[i].size(); j++) {
                cout <<j<< " X= " << contours[i][j].x << " Y= " << contours[i][j].y << endl;
            }
        }
    }
    namedWindow( "Contours", CV_WINDOW_AUTOSIZE );
    imshow( "Contours", drawing );
}
