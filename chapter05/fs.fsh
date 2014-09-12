uniform sampler2D s;

void main(void)
{
    gl_FragColor = texture(s, gl_FragCoord.xy / textureSize(s, 0));

}
