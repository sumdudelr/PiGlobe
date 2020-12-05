#version 100

attribute vec4 position;
varying vec3 worldPosition;

uniform mat4 og_modelViewPerspectiveMatrix;

void main()
{
    gl_Position = og_modelViewPerspectiveMatrix * position;
    worldPosition = position.xyz;
}
