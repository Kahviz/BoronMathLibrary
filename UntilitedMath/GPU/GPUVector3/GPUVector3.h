#pragma once
#include <iostream>

#include "GPU/GPUMatrix4x4/GPUMatrix4x4.h"

struct GPUVector3
{
	float x;
	float y;
	float z;
};

inline std::ostream& operator<<(std::ostream& os, const GPUVector3& v)
{
	return os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
}

inline GPUVector3 operator+(const GPUVector3& a, const GPUVector3& b)
{
	return GPUVector3{ a.x + b.x, a.y + b.y, a.z + b.z };
}

inline GPUVector3 operator-(const GPUVector3& a, const GPUVector3& b)
{
	return GPUVector3{ a.x - b.x, a.y - b.y, a.z - b.z };
}

inline GPUVector3 operator*(const GPUVector3& a, float scalar)
{
	return GPUVector3{ a.x * scalar, a.y * scalar, a.z * scalar };
}

inline GPUVector3 operator/(const GPUVector3& a, float scalar)
{
	return GPUVector3{ a.x / scalar, a.y / scalar, a.z / scalar };
}

inline float dot(const GPUVector3& a, const GPUVector3& b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

inline GPUVector3 Cross(const GPUVector3& a, const GPUVector3& b) {
	return GPUVector3(
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x
	);
}

inline float Length(const GPUVector3& v) {
	return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

inline GPUVector3 Normalize(const GPUVector3& v) {
	float len = Length(v);
	if (len == 0.0f) return GPUVector3(0, 0, 0);
	return v / len;
}

inline GPUVector3 GPUVector3TransformCoord(const GPUVector3& v, const GPUMatrix4x4& m) {
	float x = v.x * m.x.x + v.y * m.y.x + v.z * m.z.x + m.w.x;
	float y = v.x * m.x.y + v.y * m.y.y + v.z * m.z.y + m.w.y;
	float z = v.x * m.x.z + v.y * m.y.z + v.z * m.z.z + m.w.z;
	float w = v.x * m.x.w + v.y * m.y.w + v.z * m.z.w + m.w.w;

	if (w != 0.0f) {
		x /= w;
		y /= w;
		z /= w;
	}

	return { x, y, z };
}

inline GPUVector3 VectorSet(float x, float y, float z) {
	return GPUVector3(x, y, z);
}