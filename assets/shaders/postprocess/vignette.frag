#version 330

// The texture holding the scene pixels
uniform sampler2D tex;

// Read "assets/shaders/fullscreen.vert" to know what "tex_coord" holds;
in vec2 tex_coord;

out vec4 frag_color;

// Vignette is a postprocessing effect that darkens the corners of the screen
// to grab the attention of the viewer towards the center of the screen

void main(){
    //TODO: Modify this shader to apply vignette
    // To apply vignette, divide the scene color
    // by 1 + the squared length of the 2D pixel location the NDC space
    // Hint: remember that the NDC space ranges from -1 to 1
    // while the texture coordinate space ranges from 0 to 1
    // We have the pixel's texture coordinate, how can we compute its location in the NDC space?

    //vec4 color = texture2D(tex, tex_coord);
    //float vig = color.xy/(1+(tex_coord.x*tex_coord.x+tex_coord.y*tex_coord.y));
    //vec4 vig = color/(1+(tex_coord.x*tex_coord.x+tex_coord.y*tex_coord.y));
    //frag_color = vig;
    //frag_color = vec4(vig);
    //frag_color = vec4(0.0, 0.0, 0.0, 1.0);

    vec4 color = texture2D(tex, tex_coord.xy);
    frag_color = color/(1+((tex_coord.x*2-1.0)*(tex_coord.x*2-1.0)+(tex_coord.y*2-1.0)*(tex_coord.y*2-1.0)));
    
}