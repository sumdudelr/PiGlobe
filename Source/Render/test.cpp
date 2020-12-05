#include <iostream>
#include <vector>
#include <csignal>

#include "Renderer.hpp"
#include "Shader.hpp"
#include "SceneState.hpp"
#include "Ellipsoid.hpp"

static volatile int terminate;

void signal_handler(int signal) {
    if (signal == SIGINT)
        terminate = 1;
}

int main() {
    // Set up a signal handler for program exit
    std::signal(SIGINT, signal_handler);
    
    Ellipsoid globeShape = Ellipsoid(6378137.0, 6178137.0, 6356752.314245); //wgs84
    
    SceneState scenestate = SceneState();
    
    
    Renderer render;
    render.initialize();
    
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    
    
    Shader sp = Shader("GLSL/globeRayCastVS.glsl", "GLSL/globeRayCastFS.glsl");
    
    Shader solidSp = Shader("GLSL/globeRayCastVS.glsl", "GLSL/globeRayCastSolidShadedFS.glsl");
    
    
}
