Input={

}

--- 记录按键事件，键盘按下记录数+1，键盘弹起记录数-1，当记录数为0，说明此时没有按键。
--- @param key_code number @按键编码
--- @param key_action number @0松手 1按下 2持续按下
function Input.RecordKey(key_code,key_action)
    Cpp.Input.RecordKey()
end

--- 判断当前帧 键盘按键是否按下
--- @param key_code
function Input.GetKey(key_code)
    return Cpp.Input.GetKey(key_code)
end

--- 判断当前帧 键盘按键是否处于按下状态
--- @param key_code
function Input.GetKeyDown(key_code)
    return Cpp.Input.GetKeyDown(key_code)
end

--- 判断当前帧 键盘按键是否按下并松开
--- @param key_code
function Input.GetKeyUp(key_code)
    return Cpp.Input.GetKeyUp(key_code)
end

--- 刷帧
function Input.Update()
    Cpp.Input.Update()
end

--- 判断是否按了鼠标某个按钮
--- @param mouse_button_index number @0 表示主按钮（通常为左按钮），1 表示副按钮，2 表示中间按钮。
--- @return boolean
function Input.GetMouseButton(mouse_button_index)
    return Cpp.Input.GetMouseButton(mouse_button_index)
end

--- 指定鼠标按键是否处于按下的状态
--- @param mouse_button_index number @0 表示主按钮（通常为左按钮），1 表示副按钮，2 表示中间按钮。
--- @return boolean
function Input.GetMouseButtonDown(mouse_button_index)
    return Cpp.Input.GetMouseButtonDown(mouse_button_index)
end

--- 鼠标按钮是否松开
--- @param mouse_button_index number @0 表示主按钮（通常为左按钮），1 表示副按钮，2 表示中间按钮。
--- @return boolean
function Input.GetMouseButtonUp(mouse_button_index)
    return Cpp.Input.GetMouseButtonUp(mouse_button_index)
end

--- 返回鼠标位置
--- @return vec2
function Input.mousePosition()
    return Cpp.Input.mousePosition()
end

--- 设置鼠标位置
--- @return
function Input.set_mousePosition(x,y)
    Cpp.Input.set_mousePosition(x,y)
end

--- 获取鼠标滚动值
--- @return number
function Input.mouse_scroll()
    return Cpp.Input.mouse_scroll()
end

--- 记录鼠标滚轮事件
--- @param mouse_scroll number @鼠标滚动值
--- @return boolean
function Input.RecordScroll(mouse_scroll)
    Cpp.Input.RecordScroll(mouse_scroll)
end