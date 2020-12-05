#pragma once

#include <cmath>

#include <glm/glm.hpp>

class Camera {
public:
    glm::dvec3 Eye;
    glm::dvec3 Target;
    glm::dvec3 Up;
    glm::vec3 EyeHigh() {return (glm::vec3)Eye;}
    glm::vec3 EyeLow() {return (glm::vec3)(Eye-(glm::dvec3)EyeHigh());}
    glm::dvec3 Forward() {return glm::normalize(Target - Eye);}
    glm::dvec3 Right() {return glm::normalize(glm::cross(Forward(), Up));}
    double FieldOfViewX() {return (2.0 * std::atan(AspectRatio * std::tan(FieldOfViewY * 0.5)));}
    double FieldOfViewY;
    double AspectRatio;
    double PerspectiveNearPlaneDistance;
    double PerspectiveFarPlaneDistance;
    double OrthographicNearPlaneDistance;
    double OrthographicFarPlaneDistance;
    double OrthographicDepth() {return std::abs(OrthographicFarPlaneDistance - OrthographicNearPlaneDistance);}
    double OrthographicLeft;
    double OrthographicRight;
    double OrthographicBottom;
    double OrthographicTop;
    void ZoomToTarget(double radius) {
        glm::dvec3 toEye = glm::normalize(Eye - Target);
        
        double sin = std::sin(std::min(FieldOfViewX(),FieldOfViewY) * 0.5);
        double distance = (radius / sin);
        Eye = Target + (distance * toEye);
    }
    
    Camera() {
        Eye = glm::dvec3(0.0, -1.0, 0.0);
        Target = glm::dvec3(0.0);
        Up = glm::dvec3(0.0, 0.0, 1.0);
        
        FieldOfViewY = M_PI / 6.0;
        AspectRatio = 1.0;
        
        PerspectiveNearPlaneDistance = 0.01;
        PerspectiveFarPlaneDistance = 1.0;
        
        OrthographicLeft = 0.0;
        OrthographicRight = 1.0;
        
        OrthographicBottom = 0.0;
        OrthographicTop = 1.0;
    }
};
