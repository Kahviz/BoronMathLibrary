#pragma once
#include "../../UntilitedMath.h"

inline void StoreVector3(GPUVector3* dest, const GPUVector4& src) {
	if (!dest) return;
	dest->x = src.x;
	dest->y = src.y;
	dest->z = src.z;
}

inline void StoreVector2(GPUVector2* dest, const GPUVector3& src) {
	if (!dest) return;
	dest->x = src.x;
	dest->y = src.y;
}