require("lua_extension")

UICamera=class("UICamera",Camera)

function UICamera:ctor()
    UICamera.super.ctor(self)
end

function UICamera:InitCppComponent()
    ---@type Cpp.UICamera
    self.cpp_component_instance_=Cpp.UICamera() --创建对应的C++实例
end

function UICamera:Awake()
    UICamera.super.Awake(self)
    print("UICamera Awake")
end

function UICamera:Update()
    UICamera.super.Update(self)
    print("UICamera Update")
end