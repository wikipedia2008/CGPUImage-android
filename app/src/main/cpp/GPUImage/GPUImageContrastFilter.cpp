/**
 * Created by lvHiei on 17-4-1.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */


#include "GPUImageContrastFilter.h"
#include "GPUImageFilter.h"


// 顶点着色器
const char _contrast_vertex_shader[]=
//"precision mediump float;\n"
"attribute vec4 position;\n"
"attribute vec4 inputTextureCoordinate;\n"

"varying vec2 textureCoordinate;\n"

"void main()\n"
"{\n"
"	gl_Position = position;\n"
"	textureCoordinate = inputTextureCoordinate.xy;\n"
"}\n"
;

// 片元着色器
const char _contrast_fragment_shader[]=
"precision mediump float;\n"
"uniform sampler2D inputImageTexture;\n"
"varying vec2 textureCoordinate;\n"
"uniform float contrast;\n"

"void main()\n"
"{\n"
"	vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);\n "
"   // contrast filter \n"
"   vec4 contrastColor = vec4(((textureColor.rgb - vec3(0.5)) * contrast + vec3(0.5)), textureColor.a);\n"
"   gl_FragColor = contrastColor;\n"
"}\n"
;

GPUImageContrastFilter::GPUImageContrastFilter()
        :GPUImageFilter()
{
    m_fContrast = 1.0f;
}

GPUImageContrastFilter::~GPUImageContrastFilter()
{

}

void GPUImageContrastFilter::setContrast(float contrast)
{
    if(contrast < 1.0f){
        contrast = 1.0f;
    }

    if(contrast > 4.0f){
        contrast = 4.0f;
    }

    m_fContrast = contrast;
}

bool GPUImageContrastFilter::createVertexShader(char *vertex, int &length)
{
    int expLen = strlen(_contrast_vertex_shader);

    if(!vertex || length < expLen){
        LOGE("createVertexShader failed! vertex:%p,length:$d,expLen:%d", vertex, length, expLen);
        return false;
    }

    sprintf(vertex, _contrast_vertex_shader);
    length = expLen;

    return true;
}

bool GPUImageContrastFilter::createFragmentShader(char *fragment, int &length)
{
    int expLen = strlen(_contrast_fragment_shader);

    if(!fragment || length < expLen){
        LOGE("createFragmentShader failed! fragment:%p,length:$d,expLen:%d", fragment, length, expLen);
        return false;
    }

    sprintf(fragment, _contrast_fragment_shader);
    length = expLen;
    return true;
}

bool GPUImageContrastFilter::createProgramExtra()
{
    m_iContrastLocation = glGetUniformLocation(m_uProgram, "contrast");
    return true;
}

bool GPUImageContrastFilter::beforeDrawExtra()
{
    glUniform1f(m_iContrastLocation, m_fContrast);
    return true;
}

bool GPUImageContrastFilter::onDrawExtra()
{
    return true;
}