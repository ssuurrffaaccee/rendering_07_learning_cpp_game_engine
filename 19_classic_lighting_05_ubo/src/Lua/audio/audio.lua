
require("lua_extension")

--- 音频引擎
Audio={

}

--- 初始化fmod
function Audio.Init()
    Cpp.Audio.Init()
end

--- 刷帧
function Audio.Update()
    Cpp.Audio.Update()
end