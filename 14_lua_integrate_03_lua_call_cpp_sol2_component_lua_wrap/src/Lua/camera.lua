require("lua_extension")

Camera=class("Camera",Component)

function Camera:ctor()
    Camera.super.ctor(self)
end

function Camera:InitCppComponent()
    ---@type Cpp.Camera
    self.cpp_component_instance_=Cpp.Camera() --创建对应的C++实例
end

function Camera:Awake()
    Camera.super.Awake(self)
    print("Camera Awake")
end

function Camera:Update()
    Camera.super.Update(self)
    print("Camera Update")
end