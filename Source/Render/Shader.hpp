#pragma once

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <unordered_map>

#include <GLES2/gl2.h>

#include <glm/glm.hpp>

#include "Attribute.hpp"
#include "Uniform.hpp"

class Shader {
public:
    // The program ID
    GLuint ID;
    
    // Constructor that reads and builds the shader
    Shader(const char* vertexPath, const char* fragmentPath) {
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        // Ensure ifstream objects can throw exceptions
        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try {
            // Open files
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            std::stringstream vShaderStream, fShaderStream;
            // Read file's buffer contents into streams
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
            // Close the file handlers
            vShaderFile.close();
            fShaderFile.close();
            // Convert the stream into a string
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        }
        catch (const std::ifstream::failure &e) {
            std::cerr << "Shader file could not be read" << std::endl;
        }
        const char* vShaderCode = vertexCode.c_str();
        const char* fShaderCode = fragmentCode.c_str();
        
        // Compile the shaders
        GLuint vertex, fragment;
        int success;
        char infoLog[512];
        
        // Vertex shader
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, nullptr);
        glCompileShader(vertex);
        // Print compile errors if any
        if (!success) {
            glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
            std::cerr << "Vertex shader compilation failed\n" << infoLog << std::endl;
        }
        
        // Fragment shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, nullptr);
        glCompileShader(fragment);
        // Print compile errors if any
        glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
            std::cerr << "Fragment shader compilation failed\n" << infoLog << std::endl;
        }
        
        // Shader program
        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        glLinkProgram(ID);
        // Print linking errors if any
        glGetProgramiv(ID, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(ID, 512, nullptr, infoLog);
            std::cerr << "Program linking failed\n" << infoLog << std::endl;
        }
        
        // Delete the individual shaders
        glDeleteShader(vertex);
        glDeleteShader(fragment);
        
        // Parse the shaders to automatically find attributes
        int numberOfAttributes;
        glGetProgramiv(ID, GL_ACTIVE_ATTRIBUTES, &numberOfAttributes);
        
        int attributeNameMaxLength;
        glGetProgramiv(ID, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &attributeNameMaxLength);
        
        for (int i = 0; i < numberOfAttributes; i++) {
            int attributeNameLength;
            int attributeLength;
            GLenum attributeType;
            char attributeName[attributeNameMaxLength];
            glGetActiveAttrib(ID, i, sizeof(attributeName), &attributeNameLength, &attributeLength, &attributeType, attributeName);
            
            int attributeLocation = glGetAttribLocation(ID, attributeName);
            
            _attributes.insert({attributeName, Attribute(attributeName, attributeLocation, attributeType, attributeLength)});
        }
        
        // Parse the shaders to automatically find uniforms
        int numberOfUniforms;
        glGetProgramiv(ID, GL_ACTIVE_UNIFORMS, &numberOfUniforms);
        
        int uniformNameMaxLength;
        glGetProgramiv(ID, GL_ACTIVE_UNIFORM_MAX_LENGTH, &uniformNameMaxLength);
        
        for (int i = 0; i < numberOfUniforms; i++) {
            int uniformNameLength;
            int uniformSize;
            GLenum uniformType;
            char uniformName[uniformNameMaxLength];
            glGetActiveUniform(ID, i, sizeof(uniformName), &uniformNameLength, &uniformSize, &uniformType, uniformName);
            
            //TODO: Add support for uniform arrays
            int uniformLocation = glGetUniformLocation(ID, uniformName);
            
            _uniforms.insert({uniformName, Uniform(uniformName, uniformLocation, uniformType)});
        }
    }
    
    ~Shader() {
        glDeleteProgram(ID);
    }
    
    // Use/activate the shader
    void use();
    
    //TODO: Get and set uniforms
    
private:
    // Attributes
    std::unordered_map<std::string, Attribute> _attributes;
    // Uniforms
    std::unordered_map<std::string, Uniform> _uniforms;
};
