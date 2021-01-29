#version 330 core

in vec2 vertPos;

uniform vec4 color;
uniform bool fade;
uniform vec2 direction;

out vec4 frag_color;

void main()
{
    float alpha = 0.0;

    if (fade)
    {
        if (direction.x != 0.0)
            alpha += direction.x * (vertPos.x + 0.5); 
        if (direction.y != 0.0)
            alpha += direction.y * (0.5 - vertPos.y);
    }
    else alpha = color.a;

    frag_color = vec4(color.rgb, alpha);
}