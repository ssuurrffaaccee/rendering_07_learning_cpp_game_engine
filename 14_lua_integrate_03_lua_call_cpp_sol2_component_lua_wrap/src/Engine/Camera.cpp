#include "Camera.hpp"

//注册反射
RTTR_REGISTRATION
{
    registration::class_<Camera>("Camera")
        .constructor<>()(rttr::policy::ctor::as_raw_ptr);
}
