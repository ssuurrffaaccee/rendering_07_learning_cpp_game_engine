require("lua_extension")

--- @class RectTransform : Transform
RectTransform=class("RectTransform",Transform)

function RectTransform:ctor()
    RectTransform.super.ctor(self)
end

function RectTransform:InitCppComponent()
    ---@type Cpp.RectTransform
    self.cpp_component_instance_=Cpp.RectTransform() --创建对应的C++实例
end

--- 获取尺寸
--- @return glm.vec2 rect
function RectTransform:rect()
    return self.cpp_component_instance_:rect()
end

--- 设置尺寸
--- @param glm.vec2 rect
function RectTransform:set_rect(rect)
    self.cpp_component_instance_:set_rect(rect)
end