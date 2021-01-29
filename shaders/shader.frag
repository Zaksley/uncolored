#version 330 core

in vec2 vertPos;

uniform vec4 color;
uniform bool fade;
uniform vec2 direction;

out vec4 frag_color;

void main()
{
    float alpha = 0.0;
    float x_alpha = direction.x * vertPos.x + 0.5;
    float y_alpha = 0.5 - direction.y * vertPos.y;

    if (fade)
    {
        if (direction.x != 0.0 && direction.y != 0.0)
            alpha = x_alpha + y_alpha;
        else if (direction.x != 0.0)
            alpha = x_alpha; 
        else if (direction.y != 0.0)
            alpha = y_alpha;
    }
    else alpha = color.a;

    frag_color = vec4(color.rgb, alpha);
}