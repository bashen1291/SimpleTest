//
//  SharedStructures.h
//  testMetal
//
//  Created by zhangqiang on 15/9/18.
//  Copyright (c) 2015年 zhangqiang. All rights reserved.
//

#ifndef SharedStructures_h
#define SharedStructures_h

#ifdef METAL_ENABLE
#include <simd/simd.h>

typedef struct
{
    matrix_float4x4 modelview_projection_matrix;
    matrix_float4x4 normal_matrix;
} uniforms_t;
#endif

#endif /* SharedStructures_h */

