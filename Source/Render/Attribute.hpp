#pragma once

#include <string>

class Attribute {
public:
    std::string name;
    int location;
    GLenum type;
    int length;
    
    Attribute(std::string _name, int _location, GLenum _type, int _length) {
        name = _name;
        location = _location;
        type = _type;
        length = _length;
    }
};
