#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

// --------------------------------------------
// 计时 demo
// --------------------------------------------
void tickCountDemo()
{
    double t1 = getTickCount();
    string path = "/Users/box/1.jpeg";
    Mat img = imread(path);
    double t2 = getTickCount();
    double useTime = (t2 - t1) / getTickFrequency();
    cout << "useTime" << useTime << endl;
}

// --------------------------------------------
// 色彩空间转换 demo
// --------------------------------------------
void colorSpaceDemo()
{
    string path = "/Users/box/1.jpeg";
    Mat img = imread(path);
    Mat gray;
    cvtColor(img, gray, COLOR_BGR2GRAY);
    imshow("Gray", gray);
    waitKey(0);
    destroyAllWindows();
}

// --------------------------------------------
// 绘制矩形 demo
// --------------------------------------------
void drawDemo(){
    string path = "/Users/box/1.jpeg";
    Mat img = imread(path);

    Rect rect;
    rect.x = 200;
    rect.y = 200;
    rect.width = 200;
    rect.height = 200;
    rectangle(img, rect, Scalar(0,0,255),2, 8, 0);

    imshow("Draw", img);
    waitKey(0);
    destroyAllWindows();
}



// --------------------------------------------
// 滚动条 demo
// --------------------------------------------
Mat src, dst, m;
int lightness = 50;

void on_track(int, void *)
{
    m = Scalar(lightness, lightness, lightness);
    add(src, m, dst);
    imshow("亮度调整", dst);
}

void trackBarDemo()
{
    string path = "/Users/box/1.jpeg";
    Mat img = imread(path);
    namedWindow("亮度调整", WINDOW_AUTOSIZE);

    dst = Mat::zeros(img.size(), img.type());
    m = Mat::zeros(img.size(), img.type());
    src = img;

    int max_value = 100;
    createTrackbar("Value Bar:", "亮度调整", &lightness, max_value, on_track);
    on_track(50, 0);

    waitKey(0);
    destroyAllWindows();
}

// --------------------------------------------
// video demo
// --------------------------------------------
void videoDemo(){
    // VideoCapture capture(0);
    VideoCapture capture("/Volumes/m3/123.mp4");
    
    int width = capture.get(CAP_PROP_FRAME_WIDTH);
    int height = capture.get(CAP_PROP_FRAME_HEIGHT);
    int count = capture.get(CAP_PROP_FRAME_COUNT);
    double fps = capture.get(CAP_PROP_FPS);
    cout << width << "," << height << "," << count << "," << fps << endl;

    VideoWriter writer("/Users/box/123.mp4", capture.get(CAP_PROP_FOURCC), fps, Size(width, height), true);

    Mat frame;
    while(true){
        capture.read(frame);
        if(frame.empty()){
            break;
        }

        // flip(frame, frame, 1); // 翻转
        cvtColor(frame, frame, COLOR_BGR2GRAY);
        
        writer.write(frame);

        imshow("video", frame);
        int key = waitKey(1);// 等待10毫秒, 控制帧率
        if(key == 27){ // esc
            break;
        }
    }

    capture.release();
    writer.release();
}

int main()
{

    // tickCountDemo();

    // trackBarDemo();

    // colorSpaceDemo();

    // drawDemo();

    videoDemo();

    return 0;
}
