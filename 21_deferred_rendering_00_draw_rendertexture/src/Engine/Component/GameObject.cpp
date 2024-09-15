#include "Engine/Component/GameObject.hpp"
#include <rttr/registration>
#include "Engine/Component/Component.hpp"
#include "Engine/Utils/Debug.hpp"

using namespace rttr;

Tree GameObject::game_object_tree_;//用树存储所有的GameObject。

GameObject::GameObject(std::string name): Tree::Node(),layer_(0x01) {
    set_name(name);
    game_object_tree_.root_node()->AddChild(this);
}

GameObject::~GameObject() {
    DEBUG_LOG_INFO("GameObject::~GameObject");
}


bool GameObject::SetParent(GameObject* parent){
    if(parent== nullptr){
        DEBUG_LOG_ERROR("parent null");
        return false;
    }
    parent->AddChild(this);
    return true;
}

GameObject* GameObject::Find(std::string name) {
    GameObject* game_object_find= nullptr;
    game_object_tree_.Find(game_object_tree_.root_node(), [&name](Tree::Node* node){
        GameObject* game_object=dynamic_cast<GameObject*>(node);
        if(game_object->name()==name){
            return true;
        }
        return false;
    }, reinterpret_cast<Node **>(&game_object_find));
    return game_object_find;
}

/// 附加组件实例
/// \param component_instance_table
void GameObject::AttachComponent(Component* component){
    component->set_game_object(this);
    //获取类名
    type t=type::get(*component);
    // std::string component_type_name=t.get_name().to_string();
    auto parent_types = t.get_base_classes();
    std::string component_type_name;
    if(parent_types.size()<2){
        component_type_name = t.get_name().to_string();
    }else{
        component_type_name = (++parent_types.begin())->get_name().to_string();      
    }
    if(components_map_.find(component_type_name)==components_map_.end()){
        std::vector<Component*> component_vec;
        component_vec.push_back(component);
        components_map_[component_type_name]=component_vec;
    }else{
        components_map_[component_type_name].push_back(component);
    }
}

/// 遍历组件
/// \param func
void GameObject::ForeachComponent(std::function<void(Component*)> func) {
    for (auto& v : components_map_){
        for (auto& iter : v.second){
            Component* component=iter;
            func(component);
        }
    }
}

/// 遍历GameObject
/// \param func
void GameObject::Foreach(std::function<void(GameObject* game_object)> func) {
    game_object_tree_.Post(game_object_tree_.root_node(),[&func](Tree::Node* node){
        auto n=node;
        GameObject* game_object= dynamic_cast<GameObject *>(n);
        func(game_object);
    });
}