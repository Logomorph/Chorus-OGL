uniform sampler2D tex;

void main()
{
	vec4 color = texture2D(tex,gl_TexCoord[0].st);
	vec4 c1 = color/gl_TexCoord[0].t;
	vec4 c2 = color/(1.0-gl_TexCoord[0].t);
	//if(gl_TexCoord[0].s<=0.5)
		//gl_FragColor = c1;
	//else
		gl_FragColor = c2/4.0;
}