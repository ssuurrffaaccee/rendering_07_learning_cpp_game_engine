#include "Engine/UI/UI_Image.hpp"

#include <rttr/registration>
#include <vector>

#include "Engine/Component/GameObject.hpp"
#include "Engine/RenderDevice/RenderDevice.hpp"
#include "Engine/Renderer/Material.hpp"
#include "Engine/Renderer/MeshRenderer.hpp"
#include "Engine/Renderer/Texture2D.hpp"
#include "Engine/Utils/Debug.hpp"
#include "Engine/RenderDevice/RenderTaskProducer.hpp"
#include "Engine/UI/RectTransform.hpp"

using namespace rttr;
RTTR_REGISTRATION{
    registration::class_<UIImage>("UIImage")
            .constructor<>()(rttr::policy::ctor::as_raw_ptr);
}

UIImage::UIImage():Component() {

}

UIImage::~UIImage() {

}

/// 指定图片路径加载并设置
/// \param texture_file_path
void UIImage::LoadTexture2D(const char* texture_file_path){
    Texture2D* texture_2d=Texture2D::LoadFromFile(texture_file_path);
    set_texture(texture_2d);
}

void UIImage::Update() {
    // Component::Update();
    if(texture2D_== nullptr){
        return;
    }
    MeshFilter* mesh_filter=game_object()->GetComponent<MeshFilter>();
    if(mesh_filter== nullptr){
        int width=texture2D_->width();
        int height=texture2D_->height();
        //从RectTransform拿到显示大小
        RectTransform* rect_transform=game_object()->GetComponent<RectTransform>();
        if(rect_transform!= nullptr){
            width=rect_transform->rect().x;
            height=rect_transform->rect().y;
        }
        //创建 MeshFilter
        float half_width=width/2;
        float half_height=height/2;
        std::vector<MeshFilter::Vertex> vertex_vector={
                { {-half_width, -half_height, 0.0f}, {1.0f,1.0f,1.0f,1.0f},   {0.f, 0.f} },
                { {half_width, -half_height, 0.0f}, {1.0f,1.0f,1.0f,1.0f},   {1.f, 0.f} },
                { {half_width,  half_height, 0.0f}, {1.0f,1.0f,1.0f,1.0f},   {1.f, 1.f} },
                { {-half_width,  half_height, 0.0f}, {1.0f,1.0f,1.0f,1.0f},   {0.f, 1.f} }
        };
        std::vector<unsigned short> index_vector={
                0,1,2,
                0,2,3
        };
        mesh_filter=game_object()->AddComponent<MeshFilter>();
        mesh_filter->CreateMesh(vertex_vector,index_vector);

        //创建 Material
        auto material=new Material();//设置材质
        material->Parse("material/ui_image_mvp.mat");
        material->SetTexture("u_diffuse_texture", texture2D_);

        //挂上 MeshRenderer 组件
        auto mesh_renderer=game_object()->AddComponent<MeshRenderer>();
        mesh_renderer->SetMaterial(material);
    }
}

void UIImage::OnPreRender() {
    Component::OnPreRender();
    RenderTaskProducer::ProduceRenderTaskSetStencilFunc(GL_EQUAL, 0x1, 0xFF);//等于1 通过测试 ,就是上次绘制的图 的范围 才通过测试。
    RenderTaskProducer::ProduceRenderTaskSetStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);//没有通过测试的，保留原来的，也就是保留上一次的值。
}

void UIImage::OnPostRender() {
    Component::OnPostRender();
    RenderTaskProducer::ProduceRenderTaskSetEnableState(GL_STENCIL_TEST, false);
}