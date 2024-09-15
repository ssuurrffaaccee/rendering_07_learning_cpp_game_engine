require("audio/studio/audio_studio_event")


--- 音频引擎
AudioStudio={

}

--- 初始化FMOD Studio
function AudioStudio:Init()
    Cpp.AudioStudio.Init()
end

--- 刷帧
function AudioStudio:Update()
    Cpp.AudioStudio.Update()
end

--- 加载 bank 文件
--- @param file_name string
--- @return
function AudioStudio:LoadBankFile(file_name)
    Cpp.AudioStudio.LoadBankFile(file_name)
end

--- 获取Event实例，如果没有就创建。
--- @param event_path string
--- @return AudioStudioEvent @返回创建的event
function AudioStudio:CreateEventInstance(event_path)
    local cpp_audio_studio_event=Cpp.AudioStudio.CreateEventInstance(event_path)
    local audio_studio_event=AudioStudioEvent.new(cpp_audio_studio_event)
    return audio_studio_event
end

--- 设置听者属性
--- @param x number
--- @param y number
--- @param z number
function AudioStudio:SetListenerAttributes(x,y,z)
    Cpp.AudioStudio.SetListenerAttributes(x,y,z)
end