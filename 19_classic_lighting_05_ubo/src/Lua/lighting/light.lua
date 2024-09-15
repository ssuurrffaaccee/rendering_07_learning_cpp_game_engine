require("lua_extension")

--- @class Light : Component @灯
Light=class("Light",Component)

function Light:ctor()
    Light.super.ctor(self)
end

function Light:InitCppComponent()
    ---@type Cpp.Light
    self.cpp_component_instance_=Cpp.Light() --创建对应的C++实例
end

function Light:color()
    return self.cpp_component_instance_:color()
end

function Light:set_color(color)
    return self.cpp_component_instance_:set_color(color)
end

function Light:intensity()
    return self.cpp_component_instance_:intensity()
end

function Light:set_intensity(intensity)
    return self.cpp_component_instance_:set_intensity(intensity)
end