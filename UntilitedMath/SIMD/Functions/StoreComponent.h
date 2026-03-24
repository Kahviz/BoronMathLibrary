#pragma once
#include "../../UntilitedMath.h"

inline void StoreVector3(Vector3* dest, const Vector4& src) {
	if (!dest) return;
	dest->set(src.x(), src.y(), src.z());
}

inline void StoreVector2(Vector2* dest, const Vector3& src) {
	if (!dest) return;
	dest->set(src.x(), src.y());
}