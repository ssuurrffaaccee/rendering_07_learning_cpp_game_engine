require("lua_extension")
require("cpp_class")

AudioStudioEvent=class("AudioStudioEvent",CppClass)

function AudioStudioEvent:ctor(cpp_class_instance)
    AudioStudioEvent.super.ctor(self,cpp_class_instance)
end

--- 实例化C++ Class
function AudioStudioEvent:InitCppClass()
    self.cpp_class_instance_=Cpp.AudioStudioEvent()
end

--- 设置Event参数
--- @param name string @参数名
--- @param value number
--- @param ignore_seek_speed boolean
function AudioStudioEvent:SetParameterByName(name,value,ignore_seek_speed)
    return self.cpp_class_instance_:SetParameterByName(name,value,ignore_seek_speed)
end

--- 设置Event 3D属性
--- @param x number
--- @param y number
--- @param z number
function AudioStudioEvent:Set3DAttribute(x,y,z)
    return self.cpp_class_instance_:Set3DAttribute(x,y,z)
end

--- 播放Event实例
function AudioStudioEvent:Start()
    return self.cpp_class_instance_:Start()
end

function AudioStudioEvent:Stop()
    return self.cpp_class_instance_:Stop()
end

--- 暂停
function AudioStudioEvent:Pause()
    return self.cpp_class_instance_:Pause()
end