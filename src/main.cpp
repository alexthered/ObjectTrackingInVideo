#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "detector.h"

using namespace std;
using namespace cv;

int main()
{
    //reading video stream
    cv::VideoCapture cap;
    std::string stringName = "http://webcam.apexnc.org/mjpg/video.mjpg?resolution=320x240&?dummy=video.mjpg";


    if (!cap.open(stringName)){
        cout << "Cannot open the stream" << endl;
        return 0;
    }

    cv::Mat frame;

    //list of object
    std::vector<Object> obj_list;

    //object detector
    detector* obj_detector = new detector();

    int frameCounter = 0;
    while (1){
        cap >> frame;
        if (frame.empty())
            break;

        //extract the object from frame
        obj_detector->run(frame, obj_list);

        //draw obj_list
        for (std::vector<Object>::iterator iter=obj_list.begin();
             iter!=obj_list.end();
             ++iter){
            cv::rectangle(frame, (*iter).rect, cv::Scalar(0,255,0),3,8,0);
        }

        //show image frame with detected object
        cv::imshow("Input video", frame);

        //if user press ESC, escape accordingly
        char c = cv::waitKey(1);
        if (c==27)
            break;
        frameCounter++;
    }

    delete obj_detector;
    cap.release();
	return 0;
}
