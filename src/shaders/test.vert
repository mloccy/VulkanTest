//Name="main"
#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;

layout(location = 2) in vec2 texcoords0;
layout(location = 3) in vec2 texcoords1;

layout(location = 4) in vec3 normal;
layout(location = 5) in vec3 tangent;
layout(location = 6) in vec3 bitangent;

layout(location = 0) out vec3 fragColor;
layout(location = 1) out vec2 outTexCoord;
layout(binding = 0) uniform ProjectionData 
{
    mat4 model;
    mat4 view;
    mat4 proj;
} projection;



out gl_PerVertex
{
    vec4 gl_Position;
};

void main()
{
    gl_Position = projection.proj * projection.view * projection.model * vec4(position, 1.0);
    
    outTexCoord = texcoords0;
    fragColor = color;
}