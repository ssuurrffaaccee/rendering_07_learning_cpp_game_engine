require("lua_extension")

--- @class CppClass @表示当前Lua Class，是对C++ Class的封装
CppClass=class("CppClass")

--- CppClass构造函数
function CppClass:ctor(...)
    self:InitCppClass(...)
end

--- CppClass构造函数，ctor_with是用来指定已有的cpp实例的.
--- @param cpp_class_instance table 对应C++端的Class实例。
function CppClass:ctor_with(cpp_class_instance,...)
    assert(cpp_class_instance,"ctor_with is used to specify an existing cpp instance.")
    self.cpp_class_instance_=cpp_class_instance
end

--- 实例化C++ Class
function CppClass:InitCppClass(...)
    --- @public field cpp_class_instance_ table @C++ Class实例
    self.cpp_class_instance_=nil
end

function CppClass:cpp_class_instance()
    return self.cpp_class_instance_
end

-- function CppClass:set_cpp_class_instance(cpp_class_instance)
--     self.cpp_class_instance=cpp_class_instance
-- end 