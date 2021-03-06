/**
 * Created by lvHiei on 17-4-13.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#include "GPUImageVibranceFilter.h"


#ifdef __GLSL_SUPPORT_HIGHP__

// 片元着色器
extern const char _vibrance_fragment_shader[] = SHADER_STR(
    varying highp vec2 textureCoordinate;

    uniform sampler2D inputImageTexture;
    uniform lowp float vibrance;

    void main() {
        lowp vec4 color = texture2D(inputImageTexture, textureCoordinate);
        lowp float average = (color.r + color.g + color.b) / 3.0;
        lowp float mx = max(color.r, max(color.g, color.b));
        lowp float amt = (mx - average) * (-vibrance * 3.0);
        color.rgb = mix(color.rgb, vec3(mx), amt);
        gl_FragColor = color;
    }
);

#else

// 片元着色器
extern const char _vibrance_fragment_shader[] = SHADER_STR(
 precision mediump float;
 varying vec2 textureCoordinate;

 uniform sampler2D inputImageTexture;
 uniform float vibrance;

 void main() {
     vec4 color = texture2D(inputImageTexture, textureCoordinate);
     float average = (color.r + color.g + color.b) / 3.0;
     float mx = max(color.r, max(color.g, color.b));
     float amt = (mx - average) * (-vibrance * 3.0);
     color.rgb = mix(color.rgb, vec3(mx), amt);
     gl_FragColor = color;
 }
);

#endif




GPUImageVibranceFilter::GPUImageVibranceFilter()
    : GPUImageFilter(_vibrance_fragment_shader)
{
    m_fVibrance = 0.0f;
//    m_fVibrance = 1.0f;

    m_iVibranceUniformLocation = -1;
}

GPUImageVibranceFilter::~GPUImageVibranceFilter()
{

}

void GPUImageVibranceFilter::setVibrance(float vibrance)
{
    m_fVibrance = vibrance;
}

void GPUImageVibranceFilter::setVibrance(int percent)
{
    float max = 1.0f;
    float min = -1.0f;

    if(percent < 0){
        percent = 0;
    }

    if(percent > 100){
        percent = 100;
    }

    float incremental = (max - min) / 100;

    float value = min + incremental * percent;
    setVibrance(value);
}

bool GPUImageVibranceFilter::createProgramExtra()
{
    m_iVibranceUniformLocation = glGetUniformLocation(m_uProgram, "vibrance");

    return GPUImageFilter::createProgramExtra();
}

bool GPUImageVibranceFilter::beforeDrawExtra()
{
    glUniform1f(m_iVibranceUniformLocation, m_fVibrance);
    return GPUImageFilter::beforeDrawExtra();
}

