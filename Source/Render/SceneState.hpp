#pragma once

#include <glm/glm.hpp>

#include "Camera.hpp"

class SceneState {
public:
    float DiffuseIntensity;
    float SpecularIntensity;
    float AmbientIntensity;
    float Shininess;
    Camera camera;
    
    glm::vec3 SunPosition;
    glm::vec3 CameraLightPosition() {return camera.Eye;}
    
    glm::mat4 ModelMatrix;
    double HighResolutionSnapScale;
    
    SceneState() {
        DiffuseIntensity = 0.65f;
        SpecularIntensity = 0.25f;
        AmbientIntensity = 0.10f;
        Shininess = 12.0f;
        camera = Camera();
        SunPosition = glm::dvec3(200000.0, 0.0, 0.0);
        ModelMatrix = glm::dmat4(1.0); // Identity matrix
        HighResolutionSnapScale = 1.0;
    }
    
};
