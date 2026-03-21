#pragma once

#include <immintrin.h>
#include <iostream>
#include <cmath>

class Matrix4x4 {
private:
    alignas(16) float data[16];
public:
    //Constructors
    Matrix4x4() {
        setIdentity();
    }

    Matrix4x4(float num) {
        setAll(num);
    }

    // Accessors
    float& operator()(int row, int col) {
        return data[row * 4 + col];
    }

    float operator()(int row, int col) const {
        return data[row * 4 + col];
    }

    float& operator[](int index) {
        return data[index];
    }

    float operator[](int index) const {
        return data[index];
    }

    float* Row(int row) {
        return &data[row * 4];
    }

    const float* RowC(int row) const {
        return &data[row * 4];
    }

    //operators
    
    Matrix4x4& operator=(const Matrix4x4& other) {
        if (this != &other) {
            __m128 row0 = _mm_load_ps(&other.data[0]);
            __m128 row1 = _mm_load_ps(&other.data[4]);
            __m128 row2 = _mm_load_ps(&other.data[8]);
            __m128 row3 = _mm_load_ps(&other.data[12]);

            _mm_store_ps(&data[0], row0);
            _mm_store_ps(&data[4], row1);
            _mm_store_ps(&data[8], row2);
            _mm_store_ps(&data[12], row3);
        }
        return *this;
    }

    bool operator==(const Matrix4x4& other) const {
        for (int i = 0; i < 16; i++) {
            if (std::abs(data[i] - other.data[i]) > 1e-6f) {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const Matrix4x4& other) const {
        return !(*this == other);
    }

    Matrix4x4 operator*(const Matrix4x4& other) const {
        Matrix4x4 result;

        __m128 row0 = _mm_load_ps(&data[0]);
        __m128 row1 = _mm_load_ps(&data[4]);
        __m128 row2 = _mm_load_ps(&data[8]);
        __m128 row3 = _mm_load_ps(&data[12]);

        __m128 col0 = _mm_load_ps(&other.data[0]);
        __m128 col1 = _mm_load_ps(&other.data[4]);
        __m128 col2 = _mm_load_ps(&other.data[8]);
        __m128 col3 = _mm_load_ps(&other.data[12]);

        _MM_TRANSPOSE4_PS(col0, col1, col2, col3);

        __m128 res_row0 = _mm_add_ps(
            _mm_add_ps(_mm_mul_ps(row0, col0), _mm_mul_ps(row0, col1)),
            _mm_add_ps(_mm_mul_ps(row0, col2), _mm_mul_ps(row0, col3))
        );

        __m128 res_row1 = _mm_add_ps(
            _mm_add_ps(_mm_mul_ps(row1, col0), _mm_mul_ps(row1, col1)),
            _mm_add_ps(_mm_mul_ps(row1, col2), _mm_mul_ps(row1, col3))
        );

        __m128 res_row2 = _mm_add_ps(
            _mm_add_ps(_mm_mul_ps(row2, col0), _mm_mul_ps(row2, col1)),
            _mm_add_ps(_mm_mul_ps(row2, col2), _mm_mul_ps(row2, col3))
        );

        __m128 res_row3 = _mm_add_ps(
            _mm_add_ps(_mm_mul_ps(row3, col0), _mm_mul_ps(row3, col1)),
            _mm_add_ps(_mm_mul_ps(row3, col2), _mm_mul_ps(row3, col3))
        );


        _MM_TRANSPOSE4_PS(res_row0, res_row1, res_row2, res_row3);

        _mm_store_ps(&result.data[0], res_row0);
        _mm_store_ps(&result.data[4], res_row1);
        _mm_store_ps(&result.data[8], res_row2);
        _mm_store_ps(&result.data[12], res_row3);

        return result;
    }

    Matrix4x4& operator*=(const Matrix4x4& other) {
        *this = *this * other;
        return *this;
    }

    Matrix4x4 operator*(float scalar) const {
        Matrix4x4 result;
        __m128 s = _mm_set1_ps(scalar);

        for (int i = 0; i < 4; i++) {
            __m128 row = _mm_load_ps(&data[i * 4]);
            __m128 scaled = _mm_mul_ps(row, s);
            _mm_store_ps(&result.data[i * 4], scaled);
        }

        return result;
    }

    Matrix4x4& operator*=(float scalar) {
        __m128 s = _mm_set1_ps(scalar);

        for (int i = 0; i < 4; i++) {
            __m128 row = _mm_load_ps(&data[i * 4]);
            row = _mm_mul_ps(row, s);
            _mm_store_ps(&data[i * 4], row);
        }

        return *this;
    }

    Matrix4x4 operator+(const Matrix4x4& other) const {
        Matrix4x4 result;

        for (int i = 0; i < 4; i++) {
            __m128 rowA = _mm_load_ps(&data[i * 4]);
            __m128 rowB = _mm_load_ps(&other.data[i * 4]);
            __m128 sum = _mm_add_ps(rowA, rowB);
            _mm_store_ps(&result.data[i * 4], sum);
        }

        return result;
    }

    Matrix4x4& operator+=(const Matrix4x4& other) {
        for (int i = 0; i < 4; i++) {
            __m128 rowA = _mm_load_ps(&data[i * 4]);
            __m128 rowB = _mm_load_ps(&other.data[i * 4]);
            rowA = _mm_add_ps(rowA, rowB);
            _mm_store_ps(&data[i * 4], rowA);
        }

        return *this;
    }

    Matrix4x4 operator-(const Matrix4x4& other) const {
        Matrix4x4 result;

        for (int i = 0; i < 4; i++) {
            __m128 rowA = _mm_load_ps(&data[i * 4]);
            __m128 rowB = _mm_load_ps(&other.data[i * 4]);
            __m128 diff = _mm_sub_ps(rowA, rowB);
            _mm_store_ps(&result.data[i * 4], diff);
        }

        return result;
    }

    Matrix4x4& operator-=(const Matrix4x4& other) {
        for (int i = 0; i < 4; i++) {
            __m128 rowA = _mm_load_ps(&data[i * 4]);
            __m128 rowB = _mm_load_ps(&other.data[i * 4]);
            rowA = _mm_sub_ps(rowA, rowB);
            _mm_store_ps(&data[i * 4], rowA);
        }

        return *this;
    }

    Matrix4x4 operator-() const {
        return *this * -1.0f;
    }

    //util
    void setAll(float num) {
        data[0] = num;
        data[1] = num;
        data[2] = num;
        data[3] = num;
        data[4] = num;
        data[5] = num;
        data[6] = num;
        data[7] = num;
        data[8] = num;
        data[9] = num;
        data[10] = num;
        data[11] = num;
        data[12] = num;
        data[13] = num;
        data[14] = num;
        data[15] = num;
    }

    float determinant() const {
        float det = 0.0f;

        float subfactor1 = data[5] * (data[10] * data[15] - data[11] * data[14]) -
            data[9] * (data[6] * data[15] - data[7] * data[14]) +
            data[13] * (data[6] * data[11] - data[7] * data[10]);

        float subfactor2 = -(data[4] * (data[10] * data[15] - data[11] * data[14]) -
            data[8] * (data[6] * data[15] - data[7] * data[14]) +
            data[12] * (data[6] * data[11] - data[7] * data[10]));

        float subfactor3 = data[4] * (data[9] * data[15] - data[11] * data[13]) -
            data[8] * (data[5] * data[15] - data[7] * data[13]) +
            data[12] * (data[5] * data[11] - data[7] * data[9]);

        float subfactor4 = -(data[4] * (data[9] * data[14] - data[10] * data[13]) -
            data[8] * (data[5] * data[14] - data[6] * data[13]) +
            data[12] * (data[5] * data[10] - data[6] * data[9]));

        det = data[0] * subfactor1 +
            data[1] * subfactor2 +
            data[2] * subfactor3 +
            data[3] * subfactor4;

        return det;
    }

    Matrix4x4 MatrixLookAtLH(const Vector3& eye, const Vector3& target, const Vector3& up) {
        Matrix4x4 forward = {};
    }

    void setIdentity() {
        memset(data, 0, sizeof(data));
        data[0] = data[5] = data[10] = data[15] = 1.0f;
    }
};

std::ostream& operator<<(std::ostream& os, const Matrix4x4& mat) {
    for (int row = 0; row < 4; row++) {
        os << "[ ";
        for (int col = 0; col < 4; col++) {
            os << mat(row, col);
            if (col < 3) os << ", ";
        }
        os << " ]\n";
    }
    return os;
}
