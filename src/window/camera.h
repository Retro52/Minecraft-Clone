//
// Created by Anton on 23.06.2021.
//

#ifndef GRAPHICS_CAMERA_H
#define GRAPHICS_CAMERA_H

#include "../OpenGL/include/glm/glm.hpp"


class Camera {
    void updateVectors();
public:
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;

    glm::vec3 position;
    float fov;
    glm::mat4 rotation;
    Camera(const glm::vec3& position, float fov);

    void rotate(float x, float y, float z);

    glm::mat4 getProjection() const;
    glm::mat4 getView() const;
};


#endif //GRAPHICS_CAMERA_H
