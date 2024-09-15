require("lua_extension")
require("cpp_class")

--- @class Environment 环境
Environment=class("Environment",CppClass)

function Environment:ctor()
    Environment.super.ctor(self)
end

--- 实例化C++ Class
function Environment:InitCppClass()
    self.cpp_class_instance_=Cpp.Environment()
end

--- 设置环境颜色
function Environment:set_ambient_color(ambient_color)
    self.cpp_class_instance_:set_ambient_color(ambient_color)
end

--- 获取环境颜色
function Environment:ambient_color()
    return self.cpp_class_instance_:ambient_color()
end

--- 设置环境强度
function Environment:set_ambient_color_intensity(ambient_color_intensity)
    self.cpp_class_instance_:set_ambient_color_intensity(ambient_color_intensity)
end

--- 获取环境颜色
function Environment:ambient_color_intensity()
    return self.cpp_class_instance_:ambient_color_intensity()
end

--- 获取环境颜色
function Environment:Update()
    self.cpp_class_instance_:Update()
end