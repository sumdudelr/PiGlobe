#pragma once

#include <glm/glm.hpp>

class Ellipsoid {
public:
    glm::dvec3 _radii;
    glm::dvec3 _radiiSquared;
    glm::dvec3 _radiiToTheFourth;
    glm::dvec3 _oneOverRadiiSquared;

    Ellipsoid(glm::dvec3 radii) {
        _radii = radii;
        _radiiSquared = glm::dvec3(
            radii.x * radii.x,
            radii.y * radii.y,
            radii.z * radii.z);
        _radiiToTheFourth = glm::dvec3(
            _radiiSquared.x * _radiiSquared.x,
            _radiiSquared.y * _radiiSquared.y,
            _radiiSquared.z * _radiiSquared.z);
        _oneOverRadiiSquared = glm::dvec3(
            1.0 / _radiiSquared.x,
            1.0 / _radiiSquared.y,
            1.0 / _radiiSquared.z);
    }
    
    Ellipsoid(double x, double y, double z) {
        glm::dvec3 radii = glm::dvec3(x,y,z);
        _radii = radii;
        _radiiSquared = glm::dvec3(
            radii.x * radii.x,
            radii.y * radii.y,
            radii.z * radii.z);
        _radiiToTheFourth = glm::dvec3(
            _radiiSquared.x * _radiiSquared.x,
            _radiiSquared.y * _radiiSquared.y,
            _radiiSquared.z * _radiiSquared.z);
        _oneOverRadiiSquared = glm::dvec3(
            1.0 / _radiiSquared.x,
            1.0 / _radiiSquared.y,
            1.0 / _radiiSquared.z);
    }
    
};


