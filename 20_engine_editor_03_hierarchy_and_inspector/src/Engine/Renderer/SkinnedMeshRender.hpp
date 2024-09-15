#pragma once
#include "Engine/Renderer/MeshRenderer.hpp"

/// 骨骼蒙皮动画渲染器
class SkinnedMeshRenderer : public MeshRenderer {
public:
    SkinnedMeshRenderer();
    ~SkinnedMeshRenderer();

public:
    // 刷帧，Update在Render之前，在Update里计算最新的蒙皮Mesh
    void Update() override;

RTTR_ENABLE(MeshRenderer);
};
