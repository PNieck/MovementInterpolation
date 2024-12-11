#include  <simulation/views/visualization/renderObject.hpp>

#include <glm/gtc/matrix_transform.hpp>


RenderObject::RenderObject():
    color(1.f),             // white color
    scale(1.f),
    translation(0.f),
    rotationMatrix(1.f)
{
}


glm::mat4 RenderObject::ModelMatrix() const
{
    auto result = translate(glm::mat4(1.f), translation);
    result = glm::scale(result, scale);
    return  result * rotationMatrix;
}


glm::mat4 RenderObject::InverseModelMatrix() const {
    auto result = transpose(rotationMatrix);
    result = glm::scale(result, glm::vec3(1.f/scale.x, 1.f/scale.y, 1.f/scale.z));
    return translate(result, -translation);
}


void RenderObject::UpdateMesh(const std::vector<float> &vertices, const std::vector<uint32_t> &indices)
{
    mesh.Update(vertices, indices);
}


void RenderObject::Render(const PhongShader &shader) const {
    shader.SetColor(color);
    shader.SetModelMatrix(ModelMatrix());
    shader.SetModelMatrixInverse(InverseModelMatrix());

    UseMesh();

    glDrawElements(GL_TRIANGLES, mesh.GetElementsCnt(), GL_UNSIGNED_INT, nullptr);
}
