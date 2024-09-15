require("lua_extension")
require("cpp_class")

--- @class AnimationClip @骨骼动画片段
AnimationClip=class("AnimationClip",CppClass)

function AnimationClip:ctor(cpp_class_instance)
    AnimationClip.super.ctor(self,cpp_class_instance)
end

--- 实例化C++ Class
function AnimationClip:InitCppClass()
    self.cpp_class_instance_=Cpp.AnimationClip()
end

--- 加载动画片段
--- @param file_path string
function AnimationClip:LoadFromFile(file_path)
    self.cpp_class_instance_:LoadFromFile(file_path)
end

--- 获取持续时间
--- @return number
function AnimationClip:duration()
    return self.cpp_class_instance_:duration()
end

--- 播放骨骼动画
function AnimationClip:Play()
    self.cpp_class_instance_:Play()
end

--- 更新骨骼动画
function AnimationClip:Update()
    self.cpp_class_instance_:Update()
end

--- 停止播放
function AnimationClip:Stop()
    self.cpp_class_instance_:Stop()
end