#include "struct.hpp"
#include <rttr/registration>
using namespace rttr;
// 使用RTTR 对MyStruct的 Class、Method、Property与其名字进行映射。
RTTR_REGISTRATION {
  registration::class_<MyStruct>("MyStruct")
      .constructor<MyStruct>()(rttr::policy::ctor::as_raw_ptr)
      .property("data", &MyStruct::data)
      .method("func", &MyStruct::func);
}
