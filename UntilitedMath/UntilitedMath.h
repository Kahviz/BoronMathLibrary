#pragma once

#ifdef min
#undef min
#endif
#ifdef max
#undef max
#endif

#define UNTILITEDMATHversion 0.06

#include "SIMD/Vector2/Vector2.h"
#include "SIMD/Vector3/Vector3.h"
#include "SIMD/Vector4/Vector4.h"

#include "SIMD/Int3/Int3.h"
#include "SIMD/Int2/Int2.h"

#include "SIMD/Color255/Color255.h"

#include "SIMD/Matrix4x4/Matrix4x4.h"

#include "SIMD/Functions/Matrix4x4Functions.h"
#include "SIMD/Functions/StoreComponent.h"
#include "SIMD/Functions/LoadInt.h"
#include "SIMD/Functions/LoadVector.h"
#include "SIMD/Functions/Utils.h"
#include "SIMD/Functions/TransformNormal.h"
#include "SIMD/Functions/TransformVector.h"

#include "Variables.h"

//16 byte (GPU Compatable, Not SIMD)
#include "GPU/GPUVector2/GPUVector2.h"
#include "GPU/GPUVector3/GPUVector3.h"
#include "GPU/GPUVector4/GPUVector4.h"

#include "GPU/GPUInt3/GPUInt3.h"

#include "GPU/GPUMatrix4x4/GPUMatrix4x4.h"

#include "GPU/Functions/LoadGPUInt.h"
#include "GPU/Functions/StoreGPUComponent.h"
#include "GPU/Functions/TransformGPUNormal.h"





