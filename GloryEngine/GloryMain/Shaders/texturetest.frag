#version 450
#extension GL_ARB_separate_shader_objects : enable

uniform float _u_fragScalar = 1.0;

layout(binding = 1) uniform sampler2D texSampler;

//layout(location = 0) in vec3 fragColor;
layout(location = 0) in vec2 fragTexCoord;

layout(location = 0) out vec4 outColor;

void main()
{
	outColor = texture2D(texSampler, fragTexCoord) * _u_fragScalar;
}
