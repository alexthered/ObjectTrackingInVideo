#include "detector.h"

#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace std;

detector::detector()
{
    pMOG_2 = new cv::BackgroundSubtractorMOG2();
}

detector::~detector()
{
    //delete pMOG_2;
}

int detector::run(cv::Mat img_in, std::vector<Object> &obj_list)
{
    obj_list.clear();


    //first, smooth the input image
    cv::Mat smooth_img_in;
    cv::GaussianBlur(img_in, smooth_img_in, cv::Size(3,3), 0.5, 0.5);

    //perform the background subtraction
    pMOG_2->operator()(img_in, fg_img);

    //remove shadow region
    cv::threshold(fg_img, fg_img, 127, 255, cv::THRESH_BINARY);

    //post-process the foreground mask by opening operator to remove noise
    const cv::Mat element = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(3,3));
    cv::morphologyEx(fg_img, fg_img, cv::MORPH_OPEN, element);

    cv::imshow("Foreground mask", fg_img);
    //cv::waitKey(0);

    //find detected objects in the scene
    vector<vector<cv::Point> > contours;
    vector<cv::Vec4i> hierachy;

    //find contoursPoi
    cv::findContours(fg_img, contours, hierachy,
                     CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0) );

    // Approximate contours to polygons + get bounding rects and circles
    vector<vector<cv::Point> > contours_poly( contours.size() );

    for (int i=0; i<contours.size(); i++){
        cv::approxPolyDP( cv::Mat(contours[i]), contours_poly[i], 3, true );

        //get bounding Rect
        cv::Rect bdRect = cv::boundingRect(cv::Mat(contours_poly[i]));

        //append new object to the list
        if (bdRect.width > 10 && bdRect.height > 10)
            obj_list.push_back(Object(bdRect));
    }

    //std::cout << "Found " << obj_list.size() << " objects" << std::endl;

    return 0;
}


