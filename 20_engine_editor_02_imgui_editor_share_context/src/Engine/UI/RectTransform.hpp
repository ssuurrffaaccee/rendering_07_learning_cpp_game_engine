#pragma once
#include "Engine/Component/Transform.hpp"

class RectTransform : public Transform {
public:
    RectTransform();
    ~RectTransform();

    /// 获取宽高
    /// \return
    glm::vec2 rect(){
        return rect_;
    }

    void set_rect(glm::vec2 rect){
        rect_=rect;
    }
private:
    glm::vec2 rect_;//宽高

RTTR_ENABLE(Transform);
};
