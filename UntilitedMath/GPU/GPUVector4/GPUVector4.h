#pragma once

#include <iostream>

struct GPUVector4
{
	float x;
	float y;
	float z;
	float w;
};

inline std::ostream& operator<<(std::ostream& os, const GPUVector4& v)
{
	return os << "(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
}

inline GPUVector4 operator+(const GPUVector4& a, const GPUVector4& b)
{
	return GPUVector4{ a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w };
}

inline GPUVector4 operator-(const GPUVector4& a, const GPUVector4& b)
{
	return GPUVector4{ a.x - b.x, a.y - b.y, a.z - b.z,a.w - b.w };
}

inline GPUVector4 operator*(const GPUVector4& a, float scalar)
{
	return GPUVector4{ a.x * scalar, a.y * scalar, a.z * scalar, a.w * scalar };
}

inline GPUVector4 operator/(const GPUVector4& a, float scalar)
{
	return GPUVector4{ a.x / scalar, a.y / scalar, a.z / scalar, a.w / scalar };
}

inline float dot(const GPUVector4& a, const GPUVector4& b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}


inline GPUVector4 VectorSet(float x, float y, float z, float w) {
	return GPUVector4(x, y, z, w);
}

inline GPUVector4 Normalize(const GPUVector4& v) {
	float len = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
	if (len == 0.0f) return GPUVector4(0.0f, 0.0f, 0.0f, 0.0f);
	return GPUVector4(v.x / len, v.y / len, v.z / len, 0.0f);
}