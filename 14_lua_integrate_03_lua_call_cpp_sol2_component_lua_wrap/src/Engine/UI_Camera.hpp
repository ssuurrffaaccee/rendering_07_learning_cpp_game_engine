#pragma once
#include "Camera.hpp"

#include <rttr/registration>
using namespace rttr;

class UICamera:public Camera {
public:
    UICamera();
    ~UICamera();

RTTR_ENABLE();
};

