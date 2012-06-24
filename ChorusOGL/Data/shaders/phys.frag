uniform sampler2D bbMap;
varying vec2 vTexCoord;

const float blurSize = 1.0/1280.0;
void main()
{
	vec4 leftCol = texture2D(bbMap, vec2(vTexCoord.x - 1.0*blurSize, vTexCoord.y));
	vec4 rghtCol = texture2D(bbMap, vec2(vTexCoord.x + 1.0*blurSize, vTexCoord.y));
	vec4 cCol = texture2D(bbMap, vec2(vTexCoord.x, vTexCoord.y));

	if(cCol[0] == 1.0 && !(rghtCol[0] == 0.0 && rghtCol[1] == 1.0 && rghtCol[2] == 1.0))
		gl_FragColor = vec4(0.0,0.0,0.0,1.0);
	else
	if(leftCol[0] == 1.0)
	{
		if(!(cCol[0] == 0.0 && cCol[1] == 1.0 && cCol[2] == 1.0))
			gl_FragColor = vec4(1.0,0.0,0.0,1.0);
		else
			gl_FragColor = cCol;
	}
	else
		gl_FragColor = cCol;
}