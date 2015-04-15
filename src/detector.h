#ifndef DETECTOR_H
#define DETECTOR_H

/** @brief: warper for Background subtraction method in OpenCV
  * Use contour finding to find connected component
  */

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/background_segm.hpp>

#include <vector>
#include "object.h"

class detector
{
public:
    detector();
    ~detector();

    int run(cv::Mat img_in, std::vector<Object>& obj_list);

private:
    //OpenCV's background subtractor
    cv::Ptr<cv::BackgroundSubtractorMOG2> pMOG_2;
    cv::Mat fg_img;

};

#endif // DETECTOR_H
