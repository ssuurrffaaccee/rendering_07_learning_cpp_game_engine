#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <memory>
#include <list>
#include <functional>
#include "Engine/Component/Component.hpp"
#include "Engine/DataStructure/Tree.hpp"

class GameObject:public Tree::Node {
public:
    GameObject(std::string name);
    ~GameObject();

    std::string& name(){return name_;}
    void set_name(std::string name){name_=name;}

    unsigned char layer(){return layer_;}
    void set_layer(unsigned char layer){layer_=layer;}

    bool active(){return active_;}
    void set_active(bool active){active_=active;}

    /// 设置父节点
    /// \param parent
    /// \return
    bool SetParent(GameObject* parent);

    /// 全局查找GameObject
    /// \param name
    /// \return
    static GameObject* Find(std::string name);
public:
    /// 添加组件，仅用于C++中添加组件。
    /// \tparam T 组件类型
    /// \return 组件实例
    template <class T>
    T* AddComponent(){
        T* component=new T();
        AttachComponent(component);
        component->Awake();
        return dynamic_cast<T*>(component);
    }

    /// 附加组件实例
    /// \param component_instance_table
    void AttachComponent(Component* component);

    /// 获取组件，仅用于C++中添加组件。
    /// \tparam T 组件类型
    /// \return 组件实例
    template <class T>
    T* GetComponent(){
        //获取类名
        type t=type::get<T>();
        std::string component_type_name=t.get_name().to_string();
        if(components_map_.find(component_type_name)==components_map_.end()){
            return nullptr;
        }
        std::vector<Component*> component_vec=components_map_[component_type_name];
        if(component_vec.size()==0){
            return nullptr;
        }
        return dynamic_cast<T*>(component_vec[0]);
    }

    /// 遍历组件
    /// \param func
    void ForeachComponent(std::function<void(Component*)> func);

    /// 遍历GameObject
    /// \param func
    static void Foreach(std::function<void(GameObject* game_object)> func);

    std::string ToString() const& {
        std::stringstream ss;
        ss<<"GameObject:"<<name_<<";";
        ss<<"Layer:"<<layer_<<"l";
        ss<<"components:";
        for(auto& [comp_name,comp] : components_map_){
            ss<<comp_name<<",";
        }
        std::cout<<";";
        return ss.str();
    }
    /// 返回GameObject树结构
    /// \return
    static Tree& game_object_tree(){return game_object_tree_;}
private:
    std::string name_;

    unsigned char layer_;//将物体分不同的层，用于相机分层、物理碰撞分层等。

    bool active_=true;//是否激活

    std::unordered_map<std::string,std::vector<Component*>> components_map_;

    static Tree game_object_tree_;//用树存储所有的GameObject。
};
