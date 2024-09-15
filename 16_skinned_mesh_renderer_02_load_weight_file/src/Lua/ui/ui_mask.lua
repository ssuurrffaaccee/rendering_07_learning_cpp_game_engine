
--- @class UIMask : CppComponent @遮罩
UIMask=class("UIMask",Component)

function UIMask:ctor()
    UIMask.super.ctor(self)
end

function UIMask:InitCppComponent()
    ---@type Cpp.UIMask
    self.cpp_component_instance_=Cpp.UIMask() --创建对应的C++实例
end

function UIMask:texture2D()
    return self.cpp_component_instance_:texture2D()
end

function UIMask:set_texture(texture_2d)
    self.cpp_component_instance_:set_texture(texture_2d)
end

function UIMask:OnEnable()
    self.cpp_component_instance_:OnEnable()
end

function UIMask:Update()
    self.cpp_component_instance_:Update()
end

function UIMask:OnPreRender()
    self.cpp_component_instance_:OnPreRender()
end

function UIMask:OnPostRender()
    self.cpp_component_instance_:OnPostRender()
end

function UIMask:OnDisable()
    self.cpp_component_instance_:OnDisable()
end