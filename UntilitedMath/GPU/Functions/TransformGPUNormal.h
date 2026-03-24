#pragma once

#include "../GPUVector4/GPUVector4.h"
#include "../GPUMatrix4x4/GPUMatrix4x4.h"
#include "../GPUVector3/GPUVector3.h"

inline GPUVector4 TransformGPUNormal(const GPUVector4& v, const GPUMatrix4x4& m)
{
	GPUVector4 result;
	result.x = v.x * m.x.x + v.y * m.y.x + v.z * m.z.x;
	result.y = v.x * m.x.y + v.y * m.y.y + v.z * m.z.y;
	result.z = v.x * m.x.z + v.y * m.y.z + v.z * m.z.z;
	result.w = 0.0f;
	return result;
}

inline GPUVector3 TransformGPUNormal(const GPUVector3& v, const GPUMatrix4x4& m)
{
	GPUVector3 result;
	result.x = v.x * m.x.x + v.y * m.y.x + v.z * m.z.x;
	result.y = v.x * m.x.y + v.y * m.y.y + v.z * m.z.y;
	result.z = v.x * m.x.z + v.y * m.y.z + v.z * m.z.z;
	return result;
}