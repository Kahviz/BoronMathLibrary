#pragma once

#ifdef min
#undef min
#endif
#ifdef max
#undef max
#endif

#define UNTILITEDMATHversion 0.02

#include "SIMD/Vector2/Vector2.h"
#include "SIMD/Vector3/Vector3.h"
#include "SIMD/Vector4/Vector4.h"

#include "SIMD/Int3/Int3.h"
#include "SIMD/Int2/Int2.h"

#include "SIMD/Color255/Color255.h"

#include "SIMD/Matrix4x4/Matrix4x4.h"

#include "Functions/Matrix4x4Functions.h"
#include "Functions/StoreComponent.h"
#include "Functions/LoadInt.h"
#include "Functions/LoadVector.h"
#include "Functions/Utils.h"
#include "Functions/TransformNormal.h"
#include "Functions/TransformVector.h"

#include "Variables.h"

