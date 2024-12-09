#pragma once

#include "mesh.hpp"


class MeshWithNormals: private Mesh {
public:
    MeshWithNormals() = default;

    void Update(const std::vector<float>& vertices, const std::vector<uint32_t>& indices)
    {
        Mesh::Update(vertices, indices);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(sizeof(float)*3));
        glEnableVertexAttribArray(1);
    }

    [[nodiscard]]
    int GetElementsCnt() const
        { return Mesh::GetElementsCnt(); }

    void Use() const
        { Mesh::Use(); }
};
