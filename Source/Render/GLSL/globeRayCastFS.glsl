#version 100

varying vec3 worldPosition;
//out vec3 fragmentColor;

uniform mat4 og_modelZToClipCoordinates; // !! This is 4x2 in example !!
uniform vec4 og_diffuseSpecularAmbientShininess;
uniform sampler2D og_texture0;
uniform vec3 og_cameraLightPosition;
uniform vec3 og_cameraEye;
uniform vec3 u_cameraEyeSquared;
uniform vec3 u_globeOneOverRadiiSquared;
uniform bool u_useAverageDepth;

struct Intersection
{
    bool Intersects;
    float NearTime; // Along ray
    float FarTime; // Along ray
};

// Assumes ellipsoid is at (0, 0, 0)
Intersection RayIntersectEllipsoid(vec3 rayOrigin, vec3 rayOriginSquared, vec3 rayDirection, vec3 oneOverEllipsoidRadiiSquared)
{
    float a = dot(rayDirection * rayDirection, oneOverEllipsoidRadiiSquared);
    float b = 2.0 * dot(rayOrigin * rayDirection, oneOverEllipsoidRadiiSquared);
    float c = dot(rayOriginSquared, oneOverEllipsoidRadiiSquared);
    float discriminant = b * b - 4.0 * a * c;
    
    if (discriminant < 0.0)
    {
        return Intersection(false, 0.0, 0.0);
    }
    else if (discriminant == 0.0)
    {
        float time = -0.5 * b / a;
        return Intersection(true, time, time);
    }
    
    float t = -0.5 * (b + (b > 0.0 ? 1.0 : -1.0) * sqrt(discriminant));
    float root1 = t / a;
    float root2 = c / t;
    
    return Intersection(true, min(root1, root2), max(root1, root2));
}

float ComputeWorldPositionDepth(vec3 position, mat4 modelZToClipCoordinates)
{
    vec2 v = vec2(modelZToClipCoordinates * vec4(position, 1)); // clip coordinates
    v.x /= v.y; // normalized device coordinates
    v.x = (v.x + 1.0) * 0.5;
    return v.x;
}

vec3 GeodeticSurfaceNormal(vec3 positionOnEllipsoid, vec3 oneOverEllipsoidRadiiSquared)
{
    return normalize(positionOnEllipsoid * oneOverEllipsoidRadiiSquared);
}

float LightIntensity(vec3 normal, vec3 toLight, vec3 toEye, vec4 diffuseSpecularAmbientShininess)
{
    vec3 toReflectedLight = reflect(-toLight, normal);
    
    float diffuse = max(dot(toLight, normal), 0.0);
    float specular = max(dot(toReflectedLight, toEye), 0.0);
    specular = pow(specular, diffuseSpecularAmbientShininess.w);
    
    return (diffuseSpecularAmbientShininess.x * diffuse) +
        (diffuseSpecularAmbientShininess.y * specular) +
        diffuseSpecularAmbientShininess.z;
}

vec2 ComputeTextureCoordinates(vec3 normal)
{
    return vec2(atan(normal.y, normal.x) * (1.0/(2.0*radians(180.0))) + 0.5, asin(normal.z) * (1.0/radians(180.0)) + 0.5);
}

void main()
{
    vec3 rayDirection = normalize(worldPosition - og_cameraEye);
    Intersection i = RayIntersectEllipsoid(og_cameraEye, u_cameraEyeSquared, rayDirection, u_globeOneOverRadiiSquared);
    
    if (i.Intersects)
    {
        vec3 position = og_cameraEye + (i.NearTime * rayDirection);
        vec3 normal = GeodeticSurfaceNormal(position, u_globeOneOverRadiiSquared);
        
        vec3 toLight = normalize(og_cameraLightPosition - position);
        vec3 toEye = normalize(og_cameraEye - position);
        float intensity = LightIntensity(normal, toLight, toEye, og_diffuseSpecularAmbientShininess);
        
        //fragmentColor = intensity * texture(og_texture0, ComputeTextureCoordinates(normal)).rgb;
        gl_FragColor = intensity * texture2D(og_texture0, ComputeTextureCoordinates(normal));
        
        //if (u_useAverageDepth)
        //{
            //position = og_cameraEye + (mix(i.NearTime, i.FarTime, 0.5) * rayDirection);
        //}
        
        //gl_FragDepth = ComputeWorldPositionDepth(position, og_modelZToClipCoordinates);
    }
    else
    {
        discard;
    }
}
