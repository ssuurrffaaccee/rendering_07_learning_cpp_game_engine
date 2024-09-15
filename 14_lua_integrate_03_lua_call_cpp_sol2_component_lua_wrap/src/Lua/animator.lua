require("lua_extension")

Animator=class("Animator",Component)

function Animator:ctor()
    Animator.super.ctor(self)
end

function Animator:InitCppComponent()
    ---@type Cpp.Animator
    self.cpp_component_instance_=Cpp.Animator() --创建对应的C++实例
end

function Animator:Awake()
    print("Animator Awake")
end

function Animator:Update()
    print("Animator Update")
end