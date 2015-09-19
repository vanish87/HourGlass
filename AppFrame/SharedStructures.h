//
//  SharedStructures.h
//  AppFrame
//
//  Created by Yuan Li on 2015/09/19.
//  Copyright (c) 2015年 Yuan Li. All rights reserved.
//

#ifndef SharedStructures_h
#define SharedStructures_h

#include <simd/simd.h>

typedef struct
{
    matrix_float4x4 modelview_projection_matrix;
    matrix_float4x4 normal_matrix;
} uniforms_t;

#endif /* SharedStructures_h */

