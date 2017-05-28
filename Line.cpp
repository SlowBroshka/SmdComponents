//
// Created by slowbro on 20.05.17.
//
#include <iostream>
#include <math.h>
#include "Line.h"

Line::Line(Point k, Point b) : p1(k), p2(b) {}

Line::Line(){
    p1 = Point(0, 0);
    p2 = Point(0, 0);
}

double Line::CalcAngel(const Line &_line) const{
    const double dx1 = this->p1.x - this->p2.x;
    const double dy1 = this->p1.y - this->p2.y;
    const double dx2 = _line.p1.x - _line.p2.x;
    const double dy2 = _line.p1.y - _line.p2.y;

    double cosalpha = (dx1 * dx2 + dy1 * dy2)/
                      (sqrt(dx1 * dx1 + dy1 * dy1) *
                       sqrt(dx2 * dx2 + dy2 * dy2));

    /*cout<<"*this: "<<*this<<endl;

    cout<<"_line: "<<_line<<endl;
    cout<<dx1<<" "<<dx2<<" "<<dy1<<" "<<dy2<<endl;
    cout<<"dx1*dx2+dy1*dy2 "<<(dx1 * dx2 + dy1 * dy2)<<endl;
    cout<<"sqer "<<(sqrt(dx1 * dx1 + dy1 * dy1) *
                    sqrt(dx2 * dx2 + dy2 * dy2))<<endl;
    cout<<"cosalpha= "<<cosalpha <<endl;*/
    //if (cosalpha > 1 || cosalpha < -1)
      //  return 0;
    return (180 / CV_PI * acos(cosalpha));
}

const Point &Line::getP1() const {
    return p1;
}

ostream &operator<<(ostream &os, const Line &line1) {
    os << "p1: " << line1.p1 << " p2: " << line1.p2;
    return os;
}

bool Line::operator==(const Line &rhs) const {
    return p1 == rhs.p1 &&
           p2 == rhs.p2;
}

bool Line::operator!=(const Line &rhs) const {
    return !(rhs == *this);
}

const Point &Line::getP2() const {
    return p2;
}

