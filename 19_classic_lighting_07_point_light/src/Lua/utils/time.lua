require("lua_extension")

Time={

}

--- 获取游戏运行时间
--- @return number
function Time:TimeSinceStartup()
    return Cpp.Time.TimeSinceStartup()
end

--- 一帧耗时
--- @return number
function Time:delta_time()
    return Cpp.Time.delta_time()
end