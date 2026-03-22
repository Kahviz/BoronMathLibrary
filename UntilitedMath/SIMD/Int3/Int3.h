#pragma once

#include <immintrin.h>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstdlib>

#ifndef NOMINMAX
#define NOMINMAX
#endif

class Int3 {
private:
    alignas(16) int data[4];
public:
    // Constructors
    Int3() {
        data[0] = 0;
        data[1] = 0;
        data[2] = 0;
        data[3] = 0;
    }

    Int3(int xyz) {
        data[0] = xyz;
        data[1] = xyz;
        data[2] = xyz;
        data[3] = 0;
    }

    Int3(int x, int y, int z) {
        data[0] = x;
        data[1] = y;
        data[2] = z;
        data[3] = 0;
    }

    Int3(const int* arr) {
        data[0] = arr[0];
        data[1] = arr[1];
        data[2] = arr[2];
        data[3] = 0;
    }

    Int3(const Int3& other) {
        __m128i v = _mm_load_si128((__m128i*)other.data);
        _mm_store_si128((__m128i*)data, v);
    }

    // Operators
    Int3 operator+() const {
        return *this;
    }

    Int3 operator+(int scalar) const {
        Int3 result;
        __m128i a = _mm_load_si128((__m128i*)data);
        __m128i b = _mm_set1_epi32(scalar);
        __m128i sum = _mm_add_epi32(a, b);
        _mm_store_si128((__m128i*)result.data, sum);
        return result;
    }

    Int3 operator+(const Int3& other) const {
        Int3 result;
        __m128i a = _mm_load_si128((__m128i*)data);
        __m128i b = _mm_load_si128((__m128i*)other.data);
        __m128i sum = _mm_add_epi32(a, b);
        _mm_store_si128((__m128i*)result.data, sum);
        return result;
    }

    Int3& operator+=(const Int3& other) {
        __m128i a = _mm_load_si128((__m128i*)data);
        __m128i b = _mm_load_si128((__m128i*)other.data);
        __m128i sum = _mm_add_epi32(a, b);
        _mm_store_si128((__m128i*)data, sum);
        return *this;
    }

    Int3 operator-() const {
        return Int3(-data[0], -data[1], -data[2]);
    }

    Int3 operator-(int scalar) const {
        Int3 result;
        __m128i a = _mm_load_si128((__m128i*)data);
        __m128i b = _mm_set1_epi32(scalar);
        __m128i diff = _mm_sub_epi32(a, b);
        _mm_store_si128((__m128i*)result.data, diff);
        return result;
    }

    Int3 operator-(const Int3& other) const {
        Int3 result;
        __m128i a = _mm_load_si128((__m128i*)data);
        __m128i b = _mm_load_si128((__m128i*)other.data);
        __m128i diff = _mm_sub_epi32(a, b);
        _mm_store_si128((__m128i*)result.data, diff);
        return result;
    }

    Int3& operator-=(const Int3& other) {
        __m128i a = _mm_load_si128((__m128i*)data);
        __m128i b = _mm_load_si128((__m128i*)other.data);
        __m128i diff = _mm_sub_epi32(a, b);
        _mm_store_si128((__m128i*)data, diff);
        return *this;
    }

    Int3 operator*(int scalar) const {
        Int3 result;
        __m128i a = _mm_load_si128((__m128i*)data);
        __m128i b = _mm_set1_epi32(scalar);
        __m128i prod = _mm_mullo_epi32(a, b);
        _mm_store_si128((__m128i*)result.data, prod);
        return result;
    }

    Int3 operator*(const Int3& other) const {
        Int3 result;
        __m128i a = _mm_load_si128((__m128i*)data);
        __m128i b = _mm_load_si128((__m128i*)other.data);
        __m128i prod = _mm_mullo_epi32(a, b);
        _mm_store_si128((__m128i*)result.data, prod);
        return result;
    }

    Int3& operator*=(const Int3& other) {
        __m128i a = _mm_load_si128((__m128i*)data);
        __m128i b = _mm_load_si128((__m128i*)other.data);
        __m128i prod = _mm_mullo_epi32(a, b);
        _mm_store_si128((__m128i*)data, prod);
        return *this;
    }

    Int3 operator/(int scalar) const {
        if (scalar == 0) return Int3(0);
        return Int3(
            data[0] / scalar,
            data[1] / scalar,
            data[2] / scalar
        );
    }

    Int3 operator/(const Int3& other) const {
        return Int3(
            data[0] / other.data[0],
            data[1] / other.data[1],
            data[2] / other.data[2]
        );
    }

    Int3& operator/=(const Int3& other) {
        data[0] /= other.data[0];
        data[1] /= other.data[1];
        data[2] /= other.data[2];
        return *this;
    }

    // =
    Int3& operator=(const Int3& other) {
        if (this != &other) {
            __m128i v = _mm_load_si128((__m128i*)other.data);
            _mm_store_si128((__m128i*)data, v);
        }
        return *this;
    }

    bool operator==(const Int3& other) const {
        return data[0] == other.data[0] &&
            data[1] == other.data[1] &&
            data[2] == other.data[2];
    }

    bool operator!=(const Int3& other) const {
        return !(*this == other);
    }

    int x() const { return data[0]; }
    int y() const { return data[1]; }
    int z() const { return data[2]; }

    // Utility functions
    float length() const {
        __m128i int_vec = _mm_load_si128((__m128i*)data);
        __m128 a = _mm_cvtepi32_ps(int_vec);
        __m128 sq = _mm_mul_ps(a, a);

        float temp[4];
        _mm_store_ps(temp, sq);
        return std::sqrt(temp[0] + temp[1] + temp[2]);
    }

    float lengthSquared() const {
        __m128i a = _mm_load_si128((__m128i*)data);
        __m128 a_float = _mm_cvtepi32_ps(a);
        __m128 sq = _mm_mul_ps(a_float, a_float);

        __m128 sum1 = _mm_hadd_ps(sq, sq);
        __m128 sum2 = _mm_hadd_ps(sum1, sum1);

        float result;
        _mm_store_ss(&result, sum2);
        return result;
    }

    Int3 normalized() const {
        float len = length();
        if (len > 0.0f) {
            float invLen = 1.0f / len;
            return Int3(
                static_cast<int>(data[0] * invLen),
                static_cast<int>(data[1] * invLen),
                static_cast<int>(data[2] * invLen)
            );
        }
        return Int3(0);
    }

    void normalize() {
        float len = length();
        if (len > 0.0f) {
            float invLen = 1.0f / len;
            data[0] = static_cast<int>(data[0] * invLen);
            data[1] = static_cast<int>(data[1] * invLen);
            data[2] = static_cast<int>(data[2] * invLen);
        }
    }

    int dot(const Int3& other) const {
        return data[0] * other.data[0] +
            data[1] * other.data[1] +
            data[2] * other.data[2];
    }

    void set(int newX, int newY, int newZ) {
        data[0] = newX;
        data[1] = newY;
        data[2] = newZ;
    }

    void setX(int newX) { data[0] = newX; }
    void setY(int newY) { data[1] = newY; }
    void setZ(int newZ) { data[2] = newZ; }

    void set(const Int3& other) {
        __m128i v = _mm_load_si128((__m128i*)other.data);
        _mm_store_si128((__m128i*)data, v);
    }

    Int3 cross(const Int3& other) const {
        return Int3(
            data[1] * other.data[2] - data[2] * other.data[1],
            data[2] * other.data[0] - data[0] * other.data[2],
            data[0] * other.data[1] - data[1] * other.data[0]
        );
    }

    float distance(const Int3& other) const {
        return (*this - other).length();
    }

    float distanceSquared(const Int3& other) const {
        return (*this - other).lengthSquared();
    }

    Int3 lerp(const Int3& other, float t) const {
        return Int3(
            static_cast<int>(data[0] * (1.0f - t) + other.data[0] * t),
            static_cast<int>(data[1] * (1.0f - t) + other.data[1] * t),
            static_cast<int>(data[2] * (1.0f - t) + other.data[2] * t)
        );
    }

    float angle(const Int3& other) const {
        float dotProduct = static_cast<float>(dot(other));
        float lengths = length() * other.length();
        if (lengths == 0.0f) return 0.0f;
        return std::acos(dotProduct / lengths);
    }

    __m128 to_float() const {
        return _mm_cvtepi32_ps(_mm_load_si128((__m128i*)data));
    }

    Int3 projectOnto(const Int3& onto) const {
        float ontoLengthSq = onto.lengthSquared();
        if (ontoLengthSq == 0.0f) return Int3::Zero();
        float scale = static_cast<float>(dot(onto)) / ontoLengthSq;
        return Int3(
            static_cast<int>(onto.data[0] * scale),
            static_cast<int>(onto.data[1] * scale),
            static_cast<int>(onto.data[2] * scale)
        );
    }

    Int3 reflect(const Int3& normal) const {
        float dotProduct = static_cast<float>(dot(normal));
        return Int3(
            static_cast<int>(data[0] - 2.0f * dotProduct * normal.data[0]),
            static_cast<int>(data[1] - 2.0f * dotProduct * normal.data[1]),
            static_cast<int>(data[2] - 2.0f * dotProduct * normal.data[2])
        );
    }

    Int3 abs() const {
        return Int3(
            std::abs(data[0]),
            std::abs(data[1]),
            std::abs(data[2])
        );
    }

    Int3 min(const Int3& other) const {
        return Int3(
            (std::min)(data[0], other.data[0]),
            (std::min)(data[1], other.data[1]),
            (std::min)(data[2], other.data[2])
        );
    }

    Int3 max(const Int3& other) const {
        return Int3(
            (std::max)(data[0], other.data[0]),
            (std::max)(data[1], other.data[1]),
            (std::max)(data[2], other.data[2])
        );
    }

    const int* data_ptr() const { return data; }
    int* data_ptr() { return data; }

    static Int3 Zero() { return Int3(0, 0, 0); }
    static Int3 One() { return Int3(1, 1, 1); }
    static Int3 UnitX() { return Int3(1, 0, 0); }
    static Int3 UnitY() { return Int3(0, 1, 0); }
    static Int3 UnitZ() { return Int3(0, 0, 1); }
};

std::ostream& operator<<(std::ostream& os, const Int3& vec) {
    os << "(" << vec.x() << ", " << vec.y() << ", " << vec.z() << ")";
    return os;
}