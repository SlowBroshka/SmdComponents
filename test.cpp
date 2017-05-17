//
// Created by slowbro on 16.05.17.
//


//
//
//int main() {
//
//  string filename = "/home/slowbro/Изображения/Elements/4.jpg";
//  string blackwhitefilename = "blackwhitefilename";
//
//  double alpha = 0.5, beta = 0.5;
//  int ddepth = CV_16S;
//
//  Mat img, grayImg, xGrad, yGrad,
//          xGradAbs, yGradAbs, grad, blur, ad_black_white;
//
//  Mat startimage = imread(filename);
//  GaussianBlur(startimage, startimage, Size(3,3), 0, 0, BORDER_DEFAULT);
//
//  Mat blackwhite;
//
//  cvtColor(startimage, startimage, CV_RGB2GRAY);
//
//  adaptiveThreshold(startimage, blackwhite, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY_INV, 11, 0);
//
//  Sobel(blackwhite, xGrad, ddepth, 1, 0); // по Ox
//  Sobel(blackwhite, yGrad, ddepth, 0, 1); // по Oy
//  // преобразование градиентов в 8-битные
//  convertScaleAbs(xGrad, xGradAbs);
//  convertScaleAbs(yGrad, yGradAbs);
//  // поэлементное вычисление взвешенной
//  // суммы двух массивов
//  addWeighted(xGradAbs, alpha, yGradAbs, beta, 0, grad);
//
//  if (startimage.empty()){
//    cout<<"[i] Error: Cannot open image"<<endl;
//    return -1;
//  }
//
//
//  imshow(filename, startimage);
//
//  imshow(blackwhitefilename, blackwhite);
//  //imshow("adaptive", ad_black_white);
//
//  imshow("Sobel", grad);
//
//  waitKey(0);
//
//  return 0;
//}
