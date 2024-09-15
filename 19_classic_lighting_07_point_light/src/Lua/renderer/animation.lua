require("lua_extension")

--- 骨骼动画
--- @class Animation : CppComponent
Animation=class("Animation",Component)

function Animation:ctor()
    Animation.super.ctor(self)
end

function Animation:InitCppComponent()
    ---@type Cpp.Animation
    self.cpp_component_instance_=Cpp.Animation() --创建对应的C++实例
end

--- 加载 skeleton_anim 文件
--- @param path string 文件路径
--- @param alias_name string 别名，给这个动画起一个别名，方便查找
function Animation:LoadAnimationClipFromFile(path,alias_name)
    self.cpp_component_instance_:LoadAnimationClipFromFile(path,alias_name)
end

--- 播放动画
--- @param alias_name string 动画别名
function Animation:Play(alias_name)
    self.cpp_component_instance_:Play(alias_name)
end

--- 获取当前播放的动画片段
function Animation:current_animation_clip()
    return self.cpp_component_instance_:current_animation_clip()
end

function Animation:Update()
    Animation.super.Update(self)
end