#ifndef OBJECT_H
#define OBJECT_H

#pragma once
#include <opencv2/core/core.hpp>

class Object
{
public:
    Object(cv::Rect _rect = cv::Rect(0,0,0,0));

    cv::Rect rect;
};

#endif // OBJECT_H
