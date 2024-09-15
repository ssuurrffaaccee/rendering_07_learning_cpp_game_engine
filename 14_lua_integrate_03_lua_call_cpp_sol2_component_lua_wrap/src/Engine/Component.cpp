#include "Engine/Component.hpp"

//注册反射
RTTR_REGISTRATION
{
    registration::class_<Component>("Component")
            .constructor<>()(rttr::policy::ctor::as_raw_ptr);
}