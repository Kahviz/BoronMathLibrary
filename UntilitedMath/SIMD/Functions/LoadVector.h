#pragma once
#include "UntilitedMath.h"

//Vector2
inline Vector2 Vector2ToVector2(const Vector2& a) {
    return Vector2(a.x(), a.y());
}

inline Vector3 Vector2ToVector3(const Vector2& a) {
    return Vector3(a.x(), a.y(), 0.0f);
}

inline Vector4 Vector2ToVector4(const Vector2& a) {
    return Vector4(a.x(), a.y(), 0.0f, 0.0f);
}

//Vector3
inline Vector2 Vector3ToVector2(const Vector3& a) {
    return Vector2(a.x(), a.y());
}

inline Vector3 Vector3ToVector3(const Vector3& a) {
    return Vector3(a.x(), a.y(), a.z());
}

inline Vector4 Vector3ToVector4(const Vector3& a) {
    return Vector4(a.x(), a.y(), a.z(), 0.0f);
}

//Vector4
inline Vector2 Vector4ToVector2(const Vector4& a) {
    return Vector2(a.x(), a.y());
}

inline Vector3 Vector4ToVector3(const Vector4& a) {
    return Vector3(a.x(), a.y(), a.z());
}