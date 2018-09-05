const char* Rain_vert = STRINGIFY(
attribute vec4 a_position;
attribute vec2 a_texCoord;
attribute vec4 a_color;

uniform highp vec4 _RainTex_ST;
varying highp vec2 xlv_TEXCOORD0;
varying vec4 v_fragmentColor;

void main()
{
    highp vec4 tmpvar_1;
    tmpvar_1.w = 1.0;
    tmpvar_1.xyz = a_position.xyz;
    gl_Position = (CC_MVPMatrix * tmpvar_1);
//    xlv_TEXCOORD0 = ((a_texoord.xy * _RainTex_ST.xy) + _RainTex_ST.zw);
    xlv_TEXCOORD0 = a_texCoord.xy * vec2(13.37, 4.68);
    v_fragmentColor = a_color;
});
