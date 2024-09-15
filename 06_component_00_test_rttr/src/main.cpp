#include <iostream>
#include "struct.hpp"
#include "derived_struct.hpp"
#include <rttr/registration>
using namespace rttr;
int main() {
  std::cout << "Hello, World!" << std::endl;

  // 遍历成员函数(Method)、成员变量(Property)
  {
    type t = type::get<MyStruct>();
    for (auto& prop : t.get_properties())
      std::cout << "name: " << prop.get_name() << std::endl;

    for (auto& meth : t.get_methods())
      std::cout << "name: " << meth.get_name() << std::endl;
  }
  // 通过字符串反射获取Class，并调用构造函数创建实例
  {
    type t = type::get_by_name("MyStruct");

    variant var = t.create();  // 创建实例

    constructor ctor = t.get_constructor();  // 调用构造函数创建实例
    var = ctor.invoke();
    std::cout << var.get_type().get_name();  // 输出 std::shared_ptr<MyStruct>

    auto ptr = var.get_value<MyStruct*>();
    ptr->data = 1;
    ptr->func(1.0);
  }
  {
    DerivedMyStruct child_struct;
    MyStruct* p_struct = &child_struct;
    type t = type::get(*p_struct);
    std::cout<<"x\n";
    std::cout<< t.get_name().to_string()<<"\n";
  }

  return 0;
}