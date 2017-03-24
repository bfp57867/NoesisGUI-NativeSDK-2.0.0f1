//
//  SharedStructures.h
//  Sample
//
//  Created by Jesus on 20/12/16.
//  Copyright (c) 2016 Noesis Technologies. All rights reserved.
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

