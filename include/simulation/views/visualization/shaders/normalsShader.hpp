#pragma once


#include "shader.hpp"


class NormalsShader: private Shader {
public:
    NormalsShader():
        Shader(
            "../../shaders/normals.vert",
            "../../shaders/stdShader.frag",
            nullptr,
            nullptr,
            "../../shaders/normals.geom"
        ) {}

    void SetColor(const glm::vec4& color) const
        { SetVec4("color", color); }

    void SetModelMatrix(const glm::mat4& mtx) const
        { SetMatrix4("model", mtx); }

    void SetViewMatrix(const glm::mat4& mtx) const
        { SetMatrix4("view", mtx); }

    void SetProjectionMatrix(const glm::mat4& mtx) const
        { SetMatrix4("projection", mtx); }

    void Use() const
    { Shader::Use(); }
};
