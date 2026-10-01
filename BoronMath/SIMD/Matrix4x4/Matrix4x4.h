#pragma once

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <immintrin.h>
#include <iostream>

#include "../../BoronMath.h"

namespace BML {
    class Vector4;
}

#ifndef NOMINMAX
#define NOMINMAX
#endif

namespace BML {
    class Matrix4x4;

    using Mat4x4 = Matrix4x4;

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

        BML::Vector4& row0() { return reinterpret_cast<Vector4&>(data[0]); }
        BML::Vector4& row1() { return reinterpret_cast<Vector4&>(data[4]); }
        BML::Vector4& row2() { return reinterpret_cast<Vector4&>(data[8]); }
        BML::Vector4& row3() { return reinterpret_cast<Vector4&>(data[12]); }

        BML::Vector4& x() { return reinterpret_cast<Vector4&>(data[0]); }
        BML::Vector4& y() { return reinterpret_cast<Vector4&>(data[4]); }
        BML::Vector4& z() { return reinterpret_cast<Vector4&>(data[8]); }
        BML::Vector4& w() { return reinterpret_cast<Vector4&>(data[12]); }

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

        const float* data_ptr() const { return data; }
        float* data_ptr() { return data; }

        Matrix4x4 operator*(const Matrix4x4& other) const {
            Matrix4x4 result;

            for (int row = 0; row < 4; row++) {
                __m128 rowVec = _mm_load_ps(&data[row * 4]);

                for (int col = 0; col < 4; col++) {
                    __m128 colVec = _mm_set_ps(
                        other(3, col),
                        other(2, col),
                        other(1, col),
                        other(0, col)
                    );

                    __m128 mul = _mm_mul_ps(rowVec, colVec);

                    __m128 shuf = _mm_movehl_ps(mul, mul);
                    __m128 sum = _mm_add_ps(mul, shuf);
                    shuf = _mm_shuffle_ps(sum, sum, 0x55);
                    sum = _mm_add_ss(sum, shuf);

                    result(row, col) = _mm_cvtss_f32(sum);
                }
            }

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

        Matrix4x4 Matrix4x4RotationX(float angle) {
            float c = cosf(angle);
            float s = sinf(angle);

            Matrix4x4 m = {};
            m(0, 0) = 1.0f;
            m(1, 1) = c;
            m(1, 2) = s;
            m(2, 1) = -s;
            m(2, 2) = c;
            m(3, 3) = 1.0f;
            return m;
        }

        Matrix4x4 Matrix4x4RotationY(float angle) {
            float c = cosf(angle);
            float s = sinf(angle);

            Matrix4x4 m = {};
            m(0, 0) = c;
            m(0, 2) = -s;
            m(1, 1) = 1.0f;
            m(2, 0) = s;
            m(2, 2) = c;
            m(3, 3) = 1.0f;
            return m;
        }

        Matrix4x4 Matrix4x4RotationZ(float angle) {
            float c = cosf(angle);
            float s = sinf(angle);

            Matrix4x4 m = {};
            m(0, 0) = c;
            m(0, 1) = s;
            m(1, 0) = -s;
            m(1, 1) = c;
            m(2, 2) = 1.0f;
            m(3, 3) = 1.0f;
            return m;
        }

        Matrix4x4 Matrix4x4RotationRollPitchYaw(float pitch, float yaw, float roll) {
            return Matrix4x4RotationX(roll) * Matrix4x4RotationY(pitch) * Matrix4x4RotationZ(yaw);
        }

        void setIdentity() {
            memset(data, 0, sizeof(data));
            data[0] = data[5] = data[10] = data[15] = 1.0f;
        }
        Matrix4x4 transposed() const {
            Matrix4x4 result;
            for (int row = 0; row < 4; row++) {
                for (int col = 0; col < 4; col++) {
                    result(col, row) = (*this)(row, col);
                }
            }
            return result;
        }
    };

    inline std::ostream& operator<<(std::ostream& os, const Matrix4x4& mat) {
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
}