#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Object.h"
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

class Transform : public Object
{
public:

    Transform();
    Transform(const Transform& transform);


    glm::vec3 position;
    glm::vec3 scale;
    glm::vec3 rotation;
    glm::quat quaternionRotation;

    void SetPosition(const glm::vec3& translation);
    void SetScale(const glm::vec3& scaling);
    void SetQuatRotation(glm::quat quatRotation);
    void SetRotation( const glm::vec3& axis);

    glm::mat4 GetModelMatrix() const;
    glm::mat4 GetModelInverseMatrix() const;
    glm::mat4 GetModelInverseMatrixNoTranspose() const;

    glm::vec3 GetForward() const;
    glm::vec3 GetUp() const;
    glm::vec3 GetRight() const;


    void SetUp(glm::vec3 newUp);
    void SetRight(glm::vec3 newRight);
    void SetForward(glm::vec3 newForward);
    void SetOrientationFromDirections(glm::vec3 newUp, glm::vec3 newRight);

    // Inherited via Object
    void DrawProperties() override;
    void SceneDraw() override;
private:

    void UpdateQuaternionFromEuler();
    void UpdateEulerFromQuaternion();

    float positionWidth = 120;
    float rotationWidth = 120;
    float scaleWidth = 120;
    



};