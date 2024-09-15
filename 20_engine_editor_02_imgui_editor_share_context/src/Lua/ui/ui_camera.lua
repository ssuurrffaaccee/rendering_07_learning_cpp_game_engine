require("lua_extension")

--- UI相机
--- @class UICamera : Camera
UICamera=class("UICamera",Camera)

function UICamera:ctor()
    UICamera.super.ctor(self)
end

function UICamera:InitCppComponent()
    ---@type Cpp.UICamera
    self.cpp_component_instance_=Cpp.UICamera() --创建对应的C++实例
end