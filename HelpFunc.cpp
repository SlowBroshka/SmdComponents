//
// Created by slowbro on 17.05.17.
//
#include "HelpFunc.h"


double GetMiddleAngel(const vector<Line> &Horisontal);

void dbContourPrint(const vector<Point> &contour){
    cout<<"----CONTOUR dbPrint----"<<endl;
    cout<<"Contour Area: "<<contourArea(contour)<<"Points: "<<contour.size()<<endl;
    for(auto i = 0; i < contour.size(); i++){
        //cout<<"X: "<<contour[i].x<<" Y: "<<contour[i].y<<endl;
    }
}
void DrawContourbyPoints(Mat &img, const vector<Point> &Contour, const Scalar & color){
    dbContourPrint(Contour);
    for (auto i = 0; i < Contour.size(); i++){
        img.at<Vec3b>(Contour[i].y, Contour[i].x)[0] = color[0];
        img.at<Vec3b>(Contour[i].y, Contour[i].x)[1] = color[1];
        img.at<Vec3b>(Contour[i].y, Contour[i].x)[2] = color[2];
    }
}
void DrawPixelContourbyPoints(Mat &img, const vector<Point> &Contour, const Rect offset, const uchar color){
    for (auto i = 0; i < Contour.size(); i++){
        Point offpoint1;
        offpoint1.x = Contour[i].x - offset.x;
        offpoint1.y = Contour[i].y - offset.y;
        img.at<uchar>(offpoint1.y, offpoint1.x) = color;
    }
}
void DrawLineContourbyPoints(Mat &img, const vector<Point> &Contour, const Rect offset, const uchar color){
    //dbContourPrint(Contour);
    Point offpoint1;
    Point offpoint2;
    cout<<offset<<endl;
    for (auto i = 0; i < Contour.size() - 1; i++){
        offpoint1.x = Contour[i].x - offset.x;
        offpoint1.y = Contour[i].y - offset.y;
        offpoint2.x = Contour[i+1].x - offset.x;
        offpoint2.y = Contour[i+1].y - offset.y;
        line(img, offpoint1, offpoint2, color);
    }
    offpoint1.x = Contour[0].x - offset.x;
    offpoint1.y = Contour[0].y - offset.y;
    offpoint2.x = Contour[Contour.size()-1].x - offset.x;
    offpoint2.y = Contour[Contour.size()-1].y - offset.y;
    line(img, offpoint1, offpoint2, color);
}
void DrawContour(Mat &img, const vector<Point> &contour, const Scalar & color){
    for (auto i = 0; i < contour.size() - 1; i++){
        line(img, contour[i], contour[i+1], color);
    }
    line(img, contour[0], contour[contour.size()-1], color);
}

vector<Point> GetQuadranglePoints(vector<Point> &contour){
    vector<Point> out_contour_rect;
    out_contour_rect.reserve(4);
    for (auto i =0; i < 4; i++){
        out_contour_rect.push_back(contour[i]);
    }
    for(auto i = 0; i < contour.size(); i++){
        if (contour[i].x > out_contour_rect[2].x)
            out_contour_rect[2] = contour[i];
        else if (contour[i].x< out_contour_rect[0].x)
            out_contour_rect[0] = contour[i];
        else if (contour[i].y < out_contour_rect[1].y)
            out_contour_rect[1] = contour[i];
        else if (contour[i].y > out_contour_rect[3].y)
            out_contour_rect[3] = contour[i];
    }
    return (out_contour_rect);
}

Rect GetRoiRect(vector<Point> &contour){
    int MaxX = contour[0].x;
    int MinX = contour[0].x;
    int MaxY = contour[0].y;
    int MinY = contour[0].y;
    for(auto i = 0; i < contour.size(); i++){
        if (contour[i].x > MaxX)
            MaxX = contour[i].x;
        if (contour[i].x < MinX)
            MinX = contour[i].x;
        if (contour[i].y > MaxY)
            MaxY = contour[i].y;
        if (contour[i].y < MinY)
            MinY = contour[i].y;
    }
    return Rect(MinX, MinY, MaxX-MinX, MaxY-MinY);
}
size_t GetLineLenght(Point p1, Point p2){
    int dx = p1.x - p2.x;
    int dy = p1.y - p2.y;
    return size_t(sqrt(dx*dx + dy*dy)); //If use to compare delete sqrt
}

double GetAngle(const Point p1, const Point p2){
    double dx = p1.x - p2.x;
    double dy = p1.y - p2.y;
    if (dx == 0){
        return 0;
    }
    return atan(dx/dy);
}

double GetDeviation(const double angel, const double ideal){
    return abs(ideal - angel);
}

double GetOutPutAngle(Mat & src_gray) {

    double min_angle = 90;

    vector<Point> cont_points = GetMaxContour(src_gray);

    Rect ROIRect = GetRoiRect(cont_points);
    Mat ROIsrc_gray = Mat::zeros(ROIRect.height, ROIRect.width, CV_8UC1);
    Mat ROIsrc = src_gray(ROIRect);
    Mat drawingHaff(Size(ROIsrc_gray.cols, ROIsrc_gray.rows), CV_8UC3, Scalar(0, 0, 0));

    DrawLineContourbyPoints(ROIsrc_gray, cont_points, ROIRect, 255);

    vector<Vec4i> lines;
    vector<Line> Horisontal;
    vector<Line> Vertical;
    HoughLinesP(ROIsrc_gray, lines, 1, CV_PI/180, cont_points.size() / HoughConst, 0, CV_HOUGH_PROBABILISTIC);

    DistribLines(drawingHaff, lines, Horisontal, Vertical);

    vector<pair<size_t, double>> angels;
    for(auto i = 0; i < Horisontal.size(); i++){
        for(auto j = 0; j < Vertical.size(); j++){
            pair<size_t, double> ind_angel;
            ind_angel.first = size_t(j);
            ind_angel.second = Horisontal[i].CalcAngel(Vertical[j]);
            angels.push_back(ind_angel);
            if (GetDeviation(ind_angel.second, 90) < min_angle)
                min_angle = GetDeviation(ind_angel.second, 90);
        }
    }
    vector<pair<size_t, size_t>> min_angels_indexes;
    GetMinAngelsLines(Horisontal, Vertical, min_angle, angels, min_angels_indexes);

    for(auto i = 0; i < min_angels_indexes.size(); i++){
        line(drawingHaff, Horisontal[min_angels_indexes[i].first].getP1(), Horisontal[min_angels_indexes[i].first].getP2(), Scalar(255, 255, 255), 4, FILLED);
        line(drawingHaff, Vertical[min_angels_indexes[i].second].getP1(), Vertical[min_angels_indexes[i].second].getP2(), Scalar(255, 255, 255), 2, FILLED);
        cout<<"angel "<<i<<" - "<<Horisontal[min_angels_indexes[i].first].CalcAngel(Line(Point(0, 0), Point(0, 100)))<<endl;
    }
   // imwrite("/home/slowbro/Изображения/Elements/RISUNOK8.jpg", drawingHaff);

    double rotate_angle = Horisontal[min_angels_indexes[0].first].CalcAngel(Line(Point(0, 0), Point(0, 100)));
    if (rotate_angle >= 90) rotate_angle -= 90;

    //imshow("contour", drawingHaff);
    //imshow("ROI", ROIsrc_gray);
   // imshow("src_gray",src_gray);
   // imshow("Final", ROIsrc);

    return rotate_angle;
}

void GetMinAngelsLines(const vector<Line> &Horisontal, const vector<Line> &Vertical, double min_angle,
                       const vector<pair<size_t, double>> &angels, vector<pair<size_t, size_t>> &min_angels_indexes) {
    int count = 0;
    for (auto i = 0; i < Horisontal.size(); i++) {
        for (auto j = 0; j < Vertical.size(); j++) {
            if (GetDeviation(angels[count].second, 90) == min_angle){
                min_angels_indexes.push_back(pair<size_t, size_t>(i, j));
            }
            count++;
        }
    }
}

void DistribLines(const Mat &drawingHaff, const vector<Vec4i> &lines, vector<Line> &Horisontal, vector<Line> &Vertical) {
    Horisontal.push_back(Line(Point(lines[0][0], lines[0][1]), Point(lines[0][2], lines[0][3])));
    for (auto i = 1; i < lines.size(); i++){
        Point p1 = Point(lines[i][0], lines[i][1]);
        Point p2 = Point(lines[i][2], lines[i][3]);
        if (p1 != p2) {
            Line linel(p1, p2);
            double alpha = Horisontal[0].CalcAngel(linel);
            if (alpha >= 45 && alpha <= 135) {
                Horisontal.push_back(linel);
                //line(drawingHaff, linel.getP1(), linel.getP2(), Scalar(0, 0, 255), 3, FILLED);
            } else {
                //line(drawingHaff, linel.getP1(), linel.getP2(), Scalar(0, 255, 0), 3, FILLED);
                Vertical.push_back(linel);
            }
        }
    }
}

vector<Point> GetMaxContour(Mat &src_gray) {
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;

    findContours(src_gray, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

    double max_area = 0;
    int contour_num = 0;
    for (int i = 0; i < contours.size(); i++) {
        if (contourArea(contours[i]) > max_area){
            max_area = contourArea(contours[i]);
            contour_num = i;
        }
    }
    return contours[contour_num];
}
 double GetOutPutAngle2(Mat &src_gray){
     vector<Point> cont_points = GetMaxContour(src_gray);

     Rect ROIRect = GetRoiRect(cont_points);
     Mat ROIsrc_gray = Mat::zeros(ROIRect.height, ROIRect.width, CV_8UC1);
     Mat drawingHaff(Size(ROIsrc_gray.cols, ROIsrc_gray.rows), CV_8UC3, Scalar(0, 0, 0));
     DrawLineContourbyPoints(ROIsrc_gray, cont_points, ROIRect, 255);
     vector<Vec4i> lines;
     HoughLinesP(ROIsrc_gray, lines, 1, CV_PI/180, cont_points.size() / HoughConst, 0, CV_HOUGH_PROBABILISTIC);

     vector<Line> Horisontal;
     vector<Line> Vertical;
     DistribLines(drawingHaff, lines, Horisontal, Vertical);

     double middle_horisontal_angel = GetMiddleAngel(Horisontal);
     double middle_vertical_angel = GetMiddleAngel(Vertical);

     if (middle_horisontal_angel != 0 && middle_horisontal_angel != 0)
         return (middle_horisontal_angel + middle_vertical_angel) / 2.0;
     else
         return (middle_horisontal_angel == 0 ? middle_vertical_angel : middle_horisontal_angel);
 }

double GetMiddleAngel(const vector<Line> &Horisontal) {
    auto zero_counter = 0;
    double middle_angel = 0;
    for (auto i = 0; i < Horisontal.size(); i++) {
        double angle = 0;
        angle = Horisontal[i].CalcAngel(Line(Point(0, 0), Point(0, 100)));
        if (angle >= 90) angle -= 90;
        zero_counter += angle != 0 ? 1 : 0;
        middle_angel += angle;
    }
    if (middle_angel != 0)
        middle_angel /= zero_counter;
    else
        middle_angel = 0;
    return middle_angel;
}
double GetOutPutAngel3(Mat &src_gray) {


    vector<Point> cont_points = GetMaxContour(src_gray);

    Rect ROIRect = GetRoiRect(cont_points);
    Mat ROIsrc_gray = Mat::zeros(ROIRect.height, ROIRect.width, CV_8UC1);
    Mat drawingHaff(Size(ROIsrc_gray.cols, ROIsrc_gray.rows), CV_8UC3, Scalar(0, 0, 0));
    DrawPixelContourbyPoints(ROIsrc_gray, cont_points, ROIRect, 255);

    vector<Vec4i> lines;
    vector<size_t> weight;

    int rmax =  round(sqrt(src_gray.cols * src_gray.cols +
                           src_gray.rows * src_gray.rows));

    //Mat phase(Size(rmax, 180), IPL_DEPTH_16U, 1);
    Mat phase = Mat::zeros(Size(rmax, 180), CV_8UC1);

    float accuracy = 5;
    for(auto p = 0; p < cont_points.size(); p++){
        for(auto f = 0; f < 180; f++){
            uchar* pphase = phase.ptr<uchar>(f);
            float theta = (float)(f * CV_PI / 180.0);

            for (auto r = 0; r < rmax; r++){
                if (abs(((cont_points[p].y)*sin(theta) + (cont_points[p].x)*cos(theta)) - r) < accuracy){
                    pphase[r]++;
                }
            }
        }
    }

    uchar max = 0;
    pair<uchar, uchar> line;    //  angle - normal'

    for (auto i = 0; i < rmax; i++){
        for (auto j = 0; j < 180; j++){
            if (phase.at<uchar>(j, i) > max) {
                max = phase.at<uchar>(j, i);
                line.first = j;
                line.second = i;
            }
        }
    }
    cout<<"MAX: "<<(int)max<<endl;
    for (auto i = 0; i < rmax; i++){
        for (auto j = 0; j < 180; j++){
            phase.at<uchar>(j, i) = (uchar)((255 * phase.at<uchar>(j, i)) / max);
        }
    }

    int x0 = 0;
    int y0 = (int)(line.second / sin(line.first * CV_PI / 180.0));

    int x1 = ROIsrc_gray.cols;
    int y1 = (int)(-(cos(line.first * CV_PI / 180.0)/sin(line.first * CV_PI / 180.0)) * x1 +
                   (line.second / sin(line.first * CV_PI / 180.0)));


    cout<<Point(x0, y0)<<" "<<Point(x1, y1)<<endl;

    cv::line(ROIsrc_gray, Point(x0, y0), Point(x1, y1), Scalar(0, 0, 255), 3, FILLED);

    //resize(phase,phase, Size(phase.cols, phase.rows * 3), 0, 0, INTER_LINEAR);
    imshow("src_gray", ROIsrc_gray);
    //imwrite("/home/slowbro/Изображения/Elements/PHOUGHT_notresize.jpg", phase);

   // imshow("ROIsrc_gray", ROIsrc_gray);
    //imwrite("/home/slowbro/Изображения/Elements/gra1y_line.jpg", src_gray);

    return 90-line.first;

}

void RotateShowImage(const string &filename, const Mat &img, const double angle){
    Point2f pc(img.cols/2., img.rows/2.);
    Mat r = getRotationMatrix2D(pc, -angle, 1);
    Mat dst;
    warpAffine(img, dst, r, img.size());  // what size I should use?
    imshow(filename, dst);
}

Mat DrawInterface(const Mat &src, Mat &src_gray, const double angle){

    Mat srcclone = src.clone();

    vector<Point> cont_points = GetMaxContour(src_gray);
    Rect rpoints = GetRoiRect(cont_points);
    vector<Point> qpoints  = GetQuadranglePoints(cont_points);
    Point p1(qpoints[1].x, qpoints[1].y);
    Point p2(0, tan(angle * CV_PI / 180.0) * qpoints[1].x + qpoints[1].y);

    line(srcclone, p1, p2, Scalar(255, 0, 0), 2, FILLED);
    rectangle(srcclone, rpoints, Scalar(0, 255, 0), 3, FILLED);
    std::string text = std::string("Angle: " + std::to_string(angle));
    putText(srcclone, text, Point2f(10, 50), FONT_HERSHEY_PLAIN, 2, Scalar(0,0,255));

    return srcclone;

}