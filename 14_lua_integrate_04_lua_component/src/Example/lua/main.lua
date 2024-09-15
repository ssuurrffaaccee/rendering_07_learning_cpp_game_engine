require("utils/debug")
require("utils/application")
require("component/game_object")
require("component/transform")
require("login_scene")

function main()
    -- Debug.ConnectDebugServer()

    Application:set_title("lua component")
    Application:set_data_path("../../resources/")--设置资源目录
    Application:Init()--初始化引擎

    local go=GameObject.new("LoginSceneGo")
    local transform=go:AddComponent(Transform)
    print("transform:" .. tostring(transform))
    local pos=transform:position()
    print("pos:" .. tostring(pos))

    go:AddComponent(LoginScene)

    Application:Run()--开始引擎主循环
end