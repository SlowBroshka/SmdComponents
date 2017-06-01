//
// Created by slowbro on 17.05.17.
//
#include <iostream>
#include <vector>
#include <cv.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/types_c.h>
#include "Consts.h"
#include "Line.h"

using namespace std;
using namespace cv;

#ifndef SMDCOMPONENTS_HELPFUNC_H
#define SMDCOMPONENTS_HELPFUNC_H

void dbContourPrint(const vector<Point> &contour);

void DrawContour(Mat &img, const vector<Point> &contour, const Scalar & color);
void DrawContourbyPoints(Mat &img, const vector<Point> &Contour, const Scalar & color);
void DrawPixelContourbyPoints(Mat &img, const vector<Point> &Contour, const Rect offset, const uchar color);
void DrawLineContourbyPoints(Mat &img, const vector<Point> &Contour, const Rect offset, const uchar color);

vector<Point> GetQuadranglePoints(vector<Point>&);
Rect GetRoiRect(vector<Point>&);

double GetDeviation(const double, const double);

size_t GetLineLenght(Point, Point);
double GetAngle(const Point, const Point);


void DistribLines(const Mat &drawingHaff, const vector<Vec4i> &lines, vector<Line> &Horisontal, vector<Line> &Vertical);

void GetMinAngelsLines(const vector<Line> &Horisontal, const vector<Line> &Vertical, double min_angle,
                       const vector<pair<size_t, double>> &angels, vector<pair<size_t, size_t>> &min_angels_indexes);


double getAngle1(Mat &);
double getAngle2(Mat &);
double getAngle3(Mat &);
vector<Point> GetMaxContour(Mat& );

void RotateShowImage(const string &, const Mat &, const double);

Mat DrawInterface(const Mat &, Mat &, const double);


#endif //SMDCOMPONENTS_HELPFUNC_H
