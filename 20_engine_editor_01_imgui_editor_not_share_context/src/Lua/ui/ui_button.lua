require("lua_extension")

UIButton=class("UIButton",Component)

function UIButton:ctor()
    UIButton.super.ctor(self)
end

function UIButton:InitCppComponent()
    ---@type Cpp.UIButton
    self.cpp_component_instance_=Cpp.UIButton()
end

--- 设置按钮普通状态的图片
--- @param image Image 按钮普通状态的图片
function UIButton:set_image_normal(image)
    self.cpp_component_instance_:set_image_normal(image)
end

--- 设置按钮按下的图片
--- @param image Image 按钮按下状态的图片
function UIButton:set_image_press(image)
    self.cpp_component_instance_:set_image_press(image)
end

--- 设置按钮点击回调
--- @param click_callback function 按钮点击回调
function UIButton:set_click_callback(click_callback)
    self.cpp_component_instance_:set_click_callback(click_callback)
end

-- function UIButton:Update()
--     self.cpp_component_instance_:Update()
-- end