require("lua_extension")

--- @class UIImage @图片
UIImage=class("UIImage",Component)

function UIImage:ctor()
    UIImage.super.ctor(self)
end

function UIImage:InitCppComponent()
    ---@type Cpp.UIImage
    self.cpp_component_instance_=Cpp.UIImage() --创建对应的C++实例
end

function UIImage:set_texture(texture_2d)
    self.cpp_component_instance_:set_texture(texture_2d:cpp_class_instance())
end

-- function UIImage:Update()
--     self.cpp_component_instance_:Update()
-- end

-- function UIImage:OnPreRender()
--     self.cpp_component_instance_:OnPreRender()
-- end

-- function UIImage:OnPostRender()
--     self.cpp_component_instance_:OnPostRender()
-- end