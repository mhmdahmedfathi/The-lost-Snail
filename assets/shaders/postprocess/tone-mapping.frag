#version 330 core

out vec4 frag_color;
in vec2 tex_coord;

//uniform sampler2D hdrBuffer;
uniform sampler2D tex;
uniform float exposure = 1.0;

void main()
{             
    const float gamma = 2.2;
    vec3 hdrColor = texture(tex, tex_coord).rgb;
  
    // exposure tone mapping
    vec3 mapped = vec3(1.0) - exp(-hdrColor * exposure);
    // gamma correction 
    mapped = pow(mapped, vec3(1.0 / gamma));
  
    frag_color = vec4(mapped, 1.0);
} 