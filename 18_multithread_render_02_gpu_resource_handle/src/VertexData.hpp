#pragma once
#include <glm/glm.hpp>

static const glm::vec3 kPositions[3] = {
        glm::vec3{ -0.5f, -0.5f,0.0f},
        glm::vec3{  0.5f, -0.5f,0.0f},
        glm::vec3{  0.f,   0.5f,0.0f}
};

static const glm::vec4 kColors[3] = {
        glm::vec4{ 1.f, 0.f, 0.f ,1.f},
        glm::vec4{ 0.f, 1.f, 0.f ,1.f},
        glm::vec4{ 0.f, 0.f, 1.f ,1.f}
};