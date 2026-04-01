#pragma once

#include "../Matrix4x4/Matrix4x4.h"

inline Vector4 Vector4Transform(const Vector4& v, const Matrix4x4& m) {
    float x = v.x();
    float y = v.y();
    float z = v.z();
    float w = v.w();

    float resultX = m(0, 0) * x + m(0, 1) * y + m(0, 2) * z + m(0, 3) * w;
    float resultY = m(1, 0) * x + m(1, 1) * y + m(1, 2) * z + m(1, 3) * w;
    float resultZ = m(2, 0) * x + m(2, 1) * y + m(2, 2) * z + m(2, 3) * w;
    float resultW = m(3, 0) * x + m(3, 1) * y + m(3, 2) * z + m(3, 3) * w;

    if (resultW != 0.0f && resultW != 1.0f) {
        float invW = 1.0f / resultW;
        resultX *= invW;
        resultY *= invW;
        resultZ *= invW;
        resultW = 1.0f;
    }

    return Vector4(resultX, resultY, resultZ, resultW);
}