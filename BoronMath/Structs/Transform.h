#pragma once
#include <SIMD/Vector3/Vector3.h>

struct Transform {
    Vector3 Position{ 0,0,0 };
    Vector3 Orientation{ 0,0,0 };
    Vector3 Size{ 1,1,1 };
};