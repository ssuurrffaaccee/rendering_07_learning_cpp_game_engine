
require("lua_extension")
require("lighting/light")

--- @class DirectionalLight : Light @平行光
DirectionalLight=class("DirectionalLight",Light)

function DirectionalLight:ctor()
    DirectionalLight.super.ctor(self)
end

function DirectionalLight:InitCppComponent()
    ---@type Cpp.DirectionalLight
    self.cpp_component_instance_=Cpp.DirectionalLight() --创建对应的C++实例
end