#pragma once
#include <iostream>

struct GPUVector2
{
	float x;
	float y;
	float z;

	inline GPUVector2& operator+=(const GPUVector2& other) {
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}

	inline GPUVector2& operator-=(const GPUVector2& other) {
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}
};

inline std::ostream& operator<<(std::ostream& os, const GPUVector2& v)
{
	return os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
}

inline GPUVector2 operator+(const GPUVector2& a, const GPUVector2& b)
{
	return GPUVector2{ a.x + b.x, a.y + b.y, a.z + b.z };
}

inline GPUVector2 operator-(const GPUVector2& a, const GPUVector2& b)
{
	return GPUVector2{ a.x - b.x, a.y - b.y, a.z - b.z };
}

inline GPUVector2 operator*(const GPUVector2& a, float scalar)
{
	return GPUVector2{ a.x * scalar, a.y * scalar, a.z * scalar };
}

inline GPUVector2 operator/(const GPUVector2& a, float scalar)
{
	return GPUVector2{ a.x / scalar, a.y / scalar, a.z / scalar };
}

inline float dot(const GPUVector2& a, const GPUVector2& b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

inline float MagnitudeGPUVector2(GPUVector2 a, GPUVector2 b) {
	float dx = abs(a.x - b.x);
	float dz = abs(a.z - b.z);
	float dy = abs(a.y - b.y);

	return dx + dz + dy;
}