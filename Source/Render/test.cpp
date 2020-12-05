#include <iostream>
#include <vector>
#include <csignal>

#include "Renderer.hpp"
#include "Shader.hpp"

static volatile int terminate;

void signal_handler(int signal) {
    if (signal == SIGINT)
        terminate = 1;
}

int main() {
    // Set up a signal handler for program exit
    std::signal(SIGINT, signal_handler);
    
    Renderer render;
    render.initialize();
    
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    
    
    Shader s = Shader("GLSL/globeRayCastVS.glsl", "GLSL/globeRayCastFS.glsl");
    
    
}
