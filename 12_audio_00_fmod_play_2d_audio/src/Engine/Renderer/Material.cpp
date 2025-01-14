#include "Engine/Renderer/Material.hpp"

#include <fstream>
#include <iostream>

#include "Engine/Renderer/Shader.hpp"
#include "Engine/Renderer/Texture2D.hpp"
#include "Engine/Utils/Application.hpp"
#include "glad/glad.h"
#include "rapidxml/rapidxml.hpp"
#include "rapidxml/rapidxml_print.hpp"
#include "rapidxml/rapidxml_utils.hpp"

Material::Material() {}

Material::~Material() {}

void Material::Parse(std::string material_path) {
  // 解析xml
  rapidxml::file<> xml_file((Application::data_path() + material_path).c_str());
  rapidxml::xml_document<> document;
  document.parse<0>(xml_file.data());

  // 根节点
  rapidxml::xml_node<>* material_node = document.first_node("material");
  if (material_node == nullptr) {
    return;
  }

  rapidxml::xml_attribute<>* material_shader_attribute =
      material_node->first_attribute("shader");
  if (material_shader_attribute == nullptr) {
    return;
  }
  shader_ = Shader::Find(material_shader_attribute->value());

  // 解析Texture
  rapidxml::xml_node<>* material_texture_node =
      material_node->first_node("texture");
  while (material_texture_node != nullptr) {
    rapidxml::xml_attribute<>* texture_name_attribute =
        material_texture_node->first_attribute("name");
    if (texture_name_attribute == nullptr) {
      return;
    }

    rapidxml::xml_attribute<>* texture_image_attribute =
        material_texture_node->first_attribute("image");
    if (texture_image_attribute == nullptr) {
      return;
    }

    std::string shader_property_name = texture_name_attribute->value();
    std::string image_path = texture_image_attribute->value();
    textures_.push_back(std::make_pair(texture_name_attribute->value(),
                                       Texture2D::LoadFromFile(image_path)));

    material_texture_node = material_texture_node->next_sibling("texture");
  }
}

void Material::SetUniformMatrix4fv(std::string shader_property_name,
                                   float* pointer) {
  uniform_matrix4fv_vec.push_back(
      std::make_pair(shader_property_name, pointer));
}

void Material::SetUniform1i(std::string shader_property_name, int value) {
  uniform_1i_vec.push_back(std::make_pair(shader_property_name, value));
}
void Material::SetTexture(const std::string& property, Texture2D* texture2D) {
  for (auto& pair : textures_) {
    if (pair.first == property) {
      delete (pair.second);
      pair.second = texture2D;
      break;
    }
  }
}