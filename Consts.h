//
// Created by slowbro on 18.05.17.
//
#include <iostream>
#include <vector>
#include <cv.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/types_c.h>



#ifndef SMDCOMPONENTS_CONSTS_H
#define SMDCOMPONENTS_CONSTS_H



const cv::Scalar contour_color = cv::Scalar(0, 0, 255); // BGR RED CONTOURS
const int max_adkernel = 255;

const cv::Size BLUR_RANGE  = cv::Size(3, 3);
const int CONTOUR_AREA_BORDER = 128;

const int HoughConst = 6;


#endif //SMDCOMPONENTS_CONSTS_H
