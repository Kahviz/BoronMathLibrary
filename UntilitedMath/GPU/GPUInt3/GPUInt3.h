#pragma once
#include <iostream>

#include "../GPUVector4/GPUVector4.h"

struct GPUInt3
{
	int x;
	int y;
	int z;
};

inline std::ostream& operator<<(std::ostream& os, const GPUInt3& v)
{
	return os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
}

inline GPUInt3 operator+(const GPUInt3& a, const GPUInt3& b) {
	return { a.x + b.x, a.y + b.y, a.z + b.z };
}

inline GPUInt3 operator-(const GPUInt3& a, const GPUInt3& b)
{
	return GPUInt3{ a.x - b.x, a.y - b.y, a.z - b.z };
}

inline GPUInt3 operator*(const GPUInt3& a, int scalar)
{
	return GPUInt3{ a.x * scalar, a.y * scalar, a.z * scalar };
}

inline GPUInt3 operator/(const GPUInt3& a, int scalar)
{
	return GPUInt3{ a.x / scalar, a.y / scalar, a.z / scalar };
}

inline int dot(const GPUInt3& a, const GPUInt3& b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

inline int MagnitudeGPUInt3(GPUInt3 a, GPUInt3 b) {
	int dx = abs(a.x - b.x);
	int dz = abs(a.z - b.z);
	int dy = abs(a.y - b.y);

	return dx + dz + dy;
}

inline void StoreGPUInt3(GPUInt3& Int, GPUVector4& vec) {
	Int.x = static_cast<int>(vec.x);
	Int.y = static_cast<int>(vec.y);
	Int.z = static_cast<int>(vec.z);
}