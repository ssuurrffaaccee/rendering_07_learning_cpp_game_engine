#include "derived_struct.hpp"
#include <rttr/registration>
using namespace rttr;
// 使用RTTR 对MyStruct的 Class、Method、Property与其名字进行映射。
RTTR_REGISTRATION {
  registration::class_<DerivedMyStruct>("DerivedMyStruct")
      .constructor<>()(rttr::policy::ctor::as_raw_ptr)
      .property("data", &DerivedMyStruct::data)
      .method("func", &DerivedMyStruct::func);
}