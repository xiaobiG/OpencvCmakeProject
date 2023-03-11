#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;


int main(){
    string path = "/Users/box/1.jpeg";
    Mat img = imread(path);
    imshow("Image", img);
    waitKey(0);
    return 0;
}
