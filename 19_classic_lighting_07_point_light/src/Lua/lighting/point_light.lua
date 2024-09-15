require("lua_extension")
require("lighting/light")

--- @class PointLight : Light @点光
PointLight=class("PointLight",Light)

function PointLight:ctor()
    PointLight.super.ctor(self)
end

function PointLight:InitCppComponent()
    ---@type Cpp.PointLight
    self.cpp_component_instance_=Cpp.PointLight() --创建对应的C++实例
end

--- 点光衰减常数项
function PointLight:attenuation_constant()
    return self.cpp_component_instance_:attenuation_constant()
end

--- 设置点光衰减常数项
function PointLight:set_attenuation_constant(attenuation_constant)
    return self.cpp_component_instance_:set_attenuation_constant(attenuation_constant)
end

--- 点光衰减一次项
function PointLight:attenuation_linear()
    return self.cpp_component_instance_:attenuation_linear()
end

---设置点光衰减一次项
function PointLight:set_attenuation_linear(attenuation_linear)
    return self.cpp_component_instance_:set_attenuation_linear(attenuation_linear)
end

--- 点光衰减二次项
function PointLight:attenuation_quadratic()
    return self.cpp_component_instance_:attenuation_quadratic()
end

--- 设置点光衰减二次项
function PointLight:set_attenuation_quadratic(attenuation_quadratic)
    return self.cpp_component_instance_:set_attenuation_quadratic(attenuation_quadratic)
end