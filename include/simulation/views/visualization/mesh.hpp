#pragma once

#include <vector>

#include <glad/glad.h>


class Mesh {
public:
    Mesh();
    ~Mesh();

    void Update(const std::vector<float>& vertices);

    void Use() const
        { glBindVertexArray(VAO); }

    [[nodiscard]]
    int GetElementsCnt() const
        { return elementsCnt; }

private:
    /// @brief OpenGl vector array object
    unsigned int VAO = 0;

    /// @brief OpenGl vector buffer object
    unsigned int VBO = 0;

    int elementsCnt = 0;
};
