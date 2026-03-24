#pragma once
#include "UntilitedMath.h"

inline Vector4 Vector4Transform(const Vector4& v, const Matrix4x4& m) {
    __m128 vec = _mm_loadu_ps(v.data_ptr());

    __m128 col0 = _mm_set_ps(m(4, 1), m(3, 1), m(2, 1), m(1, 1));
    __m128 col1 = _mm_set_ps(m(4, 2), m(3, 2), m(2, 2), m(1, 2));
    __m128 col2 = _mm_set_ps(m(4, 3), m(3, 3), m(2, 3), m(1, 3));
    __m128 col3 = _mm_set_ps(m(4, 4), m(3, 4), m(2, 4), m(1, 4));

    __m128 result_x = _mm_dp_ps(vec, col0, 0xF1);
    __m128 result_y = _mm_dp_ps(vec, col1, 0xF1);
    __m128 result_z = _mm_dp_ps(vec, col2, 0xF1);
    __m128 result_w = _mm_dp_ps(vec, col3, 0xF1);

    __m128 result = _mm_set_ps(
        _mm_cvtss_f32(result_w),
        _mm_cvtss_f32(result_z),
        _mm_cvtss_f32(result_y),
        _mm_cvtss_f32(result_x)
    );

    Vector4 output;
    _mm_storeu_ps(output.data_ptr(), result);
    return output;
}

inline Vector3 Vector3Transform(const Vector3& v, const Matrix4x4& m) {
    __m128 vec = _mm_loadu_ps(v.data_ptr());
    vec = _mm_and_ps(vec, _mm_set_ps(0.0f, -0.0f, -0.0f, -0.0f));

    __m128 row0 = _mm_loadu_ps(m.data_ptr() + 0);
    __m128 row1 = _mm_loadu_ps(m.data_ptr() + 4);
    __m128 row2 = _mm_loadu_ps(m.data_ptr() + 8);

    __m128 result = _mm_add_ps(
        _mm_add_ps(
            _mm_mul_ps(_mm_shuffle_ps(vec, vec, _MM_SHUFFLE(0, 0, 0, 0)), row0),
            _mm_mul_ps(_mm_shuffle_ps(vec, vec, _MM_SHUFFLE(1, 1, 1, 1)), row1)
        ),
        _mm_add_ps(
            _mm_mul_ps(_mm_shuffle_ps(vec, vec, _MM_SHUFFLE(2, 2, 2, 2)), row2),
            _mm_setzero_ps()
        )
    );

    Vector3 output;
    _mm_storeu_ps(output.data_ptr(), result);
    return output;
}