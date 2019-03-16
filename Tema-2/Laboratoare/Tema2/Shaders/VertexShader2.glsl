#version 330

// TODO: get vertex attributes from each location
layout(location=0) in vec3 v_position;
layout(location=1) in vec3 v_normal;
layout(location=3) in vec3 v_color;


// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform vec3 Culoare;
uniform float timeSeconds;

// TODO: output values to fragment shader
out vec3 frag_color;
out vec3 frag_normal;


void main()
{
	// TODO: send output to fragment shader
	frag_color = v_color;
	frag_normal = v_normal;

	float valoare  = 0.3 * sin(timeSeconds);
	if(valoare < 0){
		valoare = 0;
	}
	// TODO: compute gl_Position
	gl_Position = Projection * View * Model * vec4(v_position.x, v_position.y, v_position.z + valoare  , 1.0);
}
