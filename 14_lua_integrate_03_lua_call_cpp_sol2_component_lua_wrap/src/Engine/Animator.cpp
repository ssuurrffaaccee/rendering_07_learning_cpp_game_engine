#include "Animator.hpp"

//注册反射
RTTR_REGISTRATION
{
    registration::class_<Animator>("Animator")
        .constructor<>()(rttr::policy::ctor::as_raw_ptr);
}