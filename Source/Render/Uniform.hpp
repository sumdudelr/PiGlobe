#pragma once

#include <string>

enum UniformType {
    Int,
    Float,
    FloatVector2,
    FloatVector3,
    FloatVector4,
    IntVector2,
    IntVector3,
    IntVector4,
    Bool,
    BoolVector2,
    BoolVector3,
    BoolVector4,
    FloatMatrix22,
    FloatMatrix33,
    FloatMatrix44,
    Sampler1D,
    Sampler2D,
    Sampler2DRectangle,
    Sampler2DRectangleShadow,
    Sampler3D,
    SamplerCube,
    Sampler1DShadow,
    Sampler2DShadow,
    FloatMatrix23,
    FloatMatrix24,
    FloatMatrix32,
    FloatMatrix34,
    FloatMatrix42,
    FloatMatrix43,
    Sampler1DArray,
    Sampler2DArray,
    Sampler1DArrayShadow,
    Sampler2DArrayShadow,
    SamplerCubeShadow,
    IntSampler1D,
    IntSampler2D,
    IntSampler2DRectangle,
    IntSampler3D,
    IntSamplerCube,
    IntSampler1DArray,
    IntSampler2DArray,
    UnsignedIntSampler1D,
    UnsignedIntSampler2D,
    UnsignedIntSampler2DRectangle,
    UnsignedIntSampler3D,
    UnsignedIntSamplerCube,
    UnsignedIntSampler1DArray,
    UnsignedIntSampler2DArray
};

class Uniform {
public:
    std::string name;
    GLenum type;
    int location;
    
    Uniform(std::string _name, int _location, GLenum _type) {
        name = _name;
        type = _type;
        location = _location;
    }
};

//template<class T>
//class UniformT:public Uniform {
//private:
    //T _value;
    
//public:
    //UniformT(std::string _name, UniformType _type, 
    
    //T get() { return _value; }
    //void set(T value) { _value = value; }
//};
