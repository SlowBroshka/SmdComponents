//
// Created by slowbro on 20.05.17.
//
#ifndef SMDCOMPONENTS_LINE_H
#define SMDCOMPONENTS_LINE_H
#include <cv.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/types_c.h>

//#include "Consts.h"
//#include "HelpFunc.h"
#include <ostream>


using namespace std;
using namespace cv;

class Line {        //y = kx + b
private:
    Point p1;
    Point p2;

public:
    bool operator==(const Line &rhs) const;

    bool operator!=(const Line &rhs) const;

    Line();

    Line(const Point p1, const Point p2);
    const Point &getP1() const;
    const Point &getP2() const;


    double CalcAngel(const Line &line) const;

    friend ostream &operator<<(ostream &os, const Line &line1);
};


#endif //SMDCOMPONENTS_LINE_H
