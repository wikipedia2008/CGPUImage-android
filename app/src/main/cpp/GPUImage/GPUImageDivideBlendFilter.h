/**
 * Created by lvHiei on 17-4-10.
 * This is a project of GPUImage implemented with c++, you can
 * use it free. if you find some bug please send me a email.
 * My Email is majun_1523@163.com.
 */

#ifndef CGPUIMAGE_ANDROID_GPUIMAGEDIVIDEBLENDFILTER_H
#define CGPUIMAGE_ANDROID_GPUIMAGEDIVIDEBLENDFILTER_H


#include "GPUImageImageFilter.h"

class GPUImageDivideBlendFilter : public GPUImageImageFilter{
public:
    GPUImageDivideBlendFilter();
    virtual ~GPUImageDivideBlendFilter();

protected:
    virtual bool loadImage();
};


#endif //CGPUIMAGE_ANDROID_GPUIMAGEDIVIDEBLENDFILTER_H
