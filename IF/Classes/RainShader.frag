const char* Rain_frag = STRINGIFY(
\n#ifdef GL_ES\n
precision highp float;
precision lowp float;
\n#endif\n

uniform lowp float _FallSpeed;
uniform lowp float _RainIntensity;
uniform highp vec4 _ThunderLighting;
varying highp vec2 xlv_TEXCOORD0;
varying vec4 v_fragmentColor;

void main(void)
{
    lowp vec4 col_1;
    lowp vec2 UV_2;
    UV_2 = xlv_TEXCOORD0;
    highp vec2 tmpvar_3;
    tmpvar_3.x = UV_2.x;
    tmpvar_3.y = (UV_2.y - _FallSpeed);
    UV_2 = tmpvar_3;
    lowp vec4 tmpvar_4;
    tmpvar_4 = texture2D (CC_Texture0, UV_2);
    col_1.w = tmpvar_4.w * v_fragmentColor.w;
    col_1.xyz = (((tmpvar_4.xyz * tmpvar_4.w) * _RainIntensity) + _ThunderLighting.xyz);
    gl_FragColor = col_1;
//    gl_FragColor = v_fragmentColor;
});
