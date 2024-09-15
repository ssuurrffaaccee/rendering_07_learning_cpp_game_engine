--- @class UIText : CppComponent @文字
UIText=class("UIText",Component)

function UIText:ctor()
    UIText.super.ctor(self)
end

function UIText:InitCppComponent()
    ---@type Cpp.UIText
    self.cpp_component_instance_=Cpp.UIText()
end

function UIText:texture2D()
    return self.cpp_component_instance_:texture2D()
end

function UIText:set_font(font)
    self.cpp_component_instance_:set_font(font)
end

function UIText:set_text(text)
    self.cpp_component_instance_:set_text(text)
end

function UIText:set_color(color)
    self.cpp_component_instance_:set_color(color)
end

function UIText:color()
    return self.cpp_component_instance_:color()
end

function UIText:Update()
    self.cpp_component_instance_:Update()
end

function UIText:OnPreRender()
    self.cpp_component_instance_:OnPreRender()
end

function UIText:OnPostRender()
    self.cpp_component_instance_:OnPostRender()
end