#include "UI_Camera.hpp"

#include <rttr/registration>
using namespace rttr;

//注册反射
RTTR_REGISTRATION
{
    registration::class_<UICamera>("UICamera")
            .constructor<>()(rttr::policy::ctor::as_raw_ptr);
}

UICamera::UICamera(): Camera() {

}

UICamera::~UICamera() {

}