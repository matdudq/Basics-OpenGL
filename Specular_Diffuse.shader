#shader vertex
#version 330 core

layout(location = 0) in vec4 pos;
layout(location = 1) in vec2 tex;
layout(location = 2) in vec3 normal;

uniform mat4 u_MVP;

out vec2 v_TexCoord;
out vec3 v_Normal;
out vec3 v_WorldPosition;

void main()
{
	v_TexCoord = tex;
	v_Normal = normal;
	v_WorldPosition = pos.xyz;
	gl_Position = u_MVP * pos;
}

#shader fragment
#version 330 core

uniform sampler2D u_Texture;

in vec2 v_TexCoord;
in vec3 v_Normal;
in vec3 v_WorldPosition;

uniform vec3 u_LightDir;
uniform vec3 u_CameraPos;

out vec4 color;

void main()
{
	vec4 texColor = texture(u_Texture, v_TexCoord);

	vec4 ambient = vec4(0.1, 0.1, 1.0, 1.0);
	vec3 viewDirection = normalize(u_CameraPos - v_WorldPosition);
	vec3 halfVector = normalize(u_LightDir + viewDirection);
	float specular = pow(clamp(dot(halfVector, v_Normal), 0, 1), 100);
	float diffuse =  clamp(dot(u_LightDir, v_Normal), 0.0, 1);
	color = clamp( (ambient + specular + diffuse),0,1) * texColor;
}