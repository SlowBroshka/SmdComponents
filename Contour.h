//
// Created by slowbro on 17.05.17.
//
#include <cv.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/types_c.h>

using namespace std;
using namespace cv;

#ifndef SMDCOMPONENTS_CONTOUR_H
#define SMDCOMPONENTS_CONTOUR_H


class Contour {
public:
    vector<Point> line;

    const size_t size() const;

};


#endif //SMDCOMPONENTS_CONTOUR_H
