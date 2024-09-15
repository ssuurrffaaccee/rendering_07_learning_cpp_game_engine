

#define GLFW_INCLUDE_NONE

#include "Engine/Utils/Debug.hpp"
#include "Engine/LuaBinding/LuaBinding.hpp"

int main(void){
    //设置lua搜索目录
    LuaBinding::Init(";./lua/?.lua;");
    //绑定引擎所有类到Lua
    LuaBinding::BindLua();
    //执行lua
    LuaBinding::RunLuaFile("./lua/main.lua");
    //调用lua main()
    LuaBinding::CallLuaFunction("main");

    return 0;
}