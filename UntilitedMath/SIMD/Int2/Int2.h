#pragma once

#include <immintrin.h>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstdlib>

#ifndef NOMINMAX
#define NOMINMAX
#endif

class Int2 {
private:
    alignas(16) int data[4];
public:
    // Constructors
    Int2() {
        data[0] = 0;
        data[1] = 0;
        data[2] = 0;
        data[3] = 0;
    }

    Int2(int xy) {
        data[0] = xy;
        data[1] = xy;
        data[2] = 0;
        data[3] = 0;
    }

    Int2(int x, int y) {
        data[0] = x;
        data[1] = y;
        data[2] = 0;
        data[3] = 0;
    }

    Int2(const int* arr) {
        data[0] = arr[0];
        data[1] = arr[1];
        data[2] = 0;
        data[3] = 0;
    }

    Int2(const Int2& other) {
        __m128i v = _mm_load_si128((__m128i*)other.data);
        _mm_store_si128((__m128i*)data, v);
    }

    // Operators
    // +
    Int2 operator+() const {
        return *this;
    }

    Int2 operator+(int scalar) const {
        Int2 result;
        __m128i a = _mm_load_si128((__m128i*)data);
        __m128i b = _mm_set1_epi32(scalar);
        __m128i sum = _mm_add_epi32(a, b);
        _mm_store_si128((__m128i*)result.data, sum);
        return result;
    }

    Int2 operator+(const Int2& other) const {
        Int2 result;
        __m128i a = _mm_load_si128((__m128i*)data);
        __m128i b = _mm_load_si128((__m128i*)other.data);
        __m128i sum = _mm_add_epi32(a, b);
        _mm_store_si128((__m128i*)result.data, sum);
        return result;
    }

    Int2& operator+=(const Int2& other) {
        __m128i a = _mm_load_si128((__m128i*)data);
        __m128i b = _mm_load_si128((__m128i*)other.data);
        __m128i sum = _mm_add_epi32(a, b);
        _mm_store_si128((__m128i*)data, sum);
        return *this;
    }

    // -
    Int2 operator-() const {
        return Int2(-data[0], -data[1]);
    }

    Int2 operator-(int scalar) const {
        Int2 result;
        __m128i a = _mm_load_si128((__m128i*)data);
        __m128i b = _mm_set1_epi32(scalar);
        __m128i diff = _mm_sub_epi32(a, b);
        _mm_store_si128((__m128i*)result.data, diff);
        return result;
    }

    Int2 operator-(const Int2& other) const {
        Int2 result;
        __m128i a = _mm_load_si128((__m128i*)data);
        __m128i b = _mm_load_si128((__m128i*)other.data);
        __m128i diff = _mm_sub_epi32(a, b);
        _mm_store_si128((__m128i*)result.data, diff);
        return result;
    }

    Int2& operator-=(const Int2& other) {
        __m128i a = _mm_load_si128((__m128i*)data);
        __m128i b = _mm_load_si128((__m128i*)other.data);
        __m128i diff = _mm_sub_epi32(a, b);
        _mm_store_si128((__m128i*)data, diff);
        return *this;
    }

    // *
    Int2 operator*(int scalar) const {
        Int2 result;
        __m128i a = _mm_load_si128((__m128i*)data);
        __m128i b = _mm_set1_epi32(scalar);
        __m128i prod = _mm_mullo_epi32(a, b);
        _mm_store_si128((__m128i*)result.data, prod);
        return result;
    }

    Int2 operator*(const Int2& other) const {
        Int2 result;
        __m128i a = _mm_load_si128((__m128i*)data);
        __m128i b = _mm_load_si128((__m128i*)other.data);
        __m128i prod = _mm_mullo_epi32(a, b);
        _mm_store_si128((__m128i*)result.data, prod);
        return result;
    }

    Int2& operator*=(const Int2& other) {
        __m128i a = _mm_load_si128((__m128i*)data);
        __m128i b = _mm_load_si128((__m128i*)other.data);
        __m128i prod = _mm_mullo_epi32(a, b);
        _mm_store_si128((__m128i*)data, prod);
        return *this;
    }

    // /
    Int2 operator/(int scalar) const {
        if (scalar == 0) return Int2(0);
        return Int2(
            data[0] / scalar,
            data[1] / scalar
        );
    }

    Int2 operator/(const Int2& other) const {
        return Int2(
            data[0] / other.data[0],
            data[1] / other.data[1]
        );
    }

    Int2& operator/=(const Int2& other) {
        data[0] /= other.data[0];
        data[1] /= other.data[1];
        return *this;
    }

    // =
    Int2& operator=(const Int2& other) {
        if (this != &other) {
            __m128i v = _mm_load_si128((__m128i*)other.data);
            _mm_store_si128((__m128i*)data, v);
        }
        return *this;
    }

    bool operator==(const Int2& other) const {
        return data[0] == other.data[0] &&
            data[1] == other.data[1];
    }

    bool operator!=(const Int2& other) const {
        return !(*this == other);
    }

    int x() const { return data[0]; }
    int y() const { return data[1]; }

    // Utility functions
    float length() const {
        __m128i int_vec = _mm_load_si128((__m128i*)data);
        __m128 a = _mm_cvtepi32_ps(int_vec);
        __m128 sq = _mm_mul_ps(a, a);

        float temp[4];
        _mm_store_ps(temp, sq);
        return std::sqrt(temp[0] + temp[1]);
    }

    float lengthSquared() const {
        __m128i a = _mm_load_si128((__m128i*)data);
        __m128 a_float = _mm_cvtepi32_ps(a);
        __m128 sq = _mm_mul_ps(a_float, a_float);

        __m128 sum1 = _mm_hadd_ps(sq, sq);
        float result;
        _mm_store_ss(&result, sum1);
        return result;
    }

    Int2 normalized() const {
        float len = length();
        if (len > 0.0f) {
            float invLen = 1.0f / len;
            return Int2(
                static_cast<int>(data[0] * invLen),
                static_cast<int>(data[1] * invLen)
            );
        }
        return Int2(0);
    }

    void normalize() {
        float len = length();
        if (len > 0.0f) {
            float invLen = 1.0f / len;
            data[0] = static_cast<int>(data[0] * invLen);
            data[1] = static_cast<int>(data[1] * invLen);
        }
    }

    int dot(const Int2& other) const {
        return data[0] * other.data[0] + data[1] * other.data[1];
    }

    void set(int newX, int newY) {
        data[0] = newX;
        data[1] = newY;
    }

    void setX(int newX) { data[0] = newX; }
    void setY(int newY) { data[1] = newY; }

    void set(const Int2& other) {
        __m128i v = _mm_load_si128((__m128i*)other.data);
        _mm_store_si128((__m128i*)data, v);
    }

    int cross(const Int2& other) const {
        return data[0] * other.data[1] - data[1] * other.data[0];
    }

    float distance(const Int2& other) const {
        return (*this - other).length();
    }

    float distanceSquared(const Int2& other) const {
        return (*this - other).lengthSquared();
    }

    Int2 lerp(const Int2& other, float t) const {
        return Int2(
            static_cast<int>(data[0] * (1.0f - t) + other.data[0] * t),
            static_cast<int>(data[1] * (1.0f - t) + other.data[1] * t)
        );
    }

    float angle(const Int2& other) const {
        float dotProduct = static_cast<float>(dot(other));
        float lengths = length() * other.length();
        if (lengths == 0.0f) return 0.0f;
        return std::acos(dotProduct / lengths);
    }

    __m128 to_float() const {
        return _mm_cvtepi32_ps(_mm_load_si128((__m128i*)data));
    }

    Int2 projectOnto(const Int2& onto) const {
        float ontoLengthSq = onto.lengthSquared();
        if (ontoLengthSq == 0.0f) return Int2::Zero();
        float scale = static_cast<float>(dot(onto)) / ontoLengthSq;
        return Int2(
            static_cast<int>(onto.data[0] * scale),
            static_cast<int>(onto.data[1] * scale)
        );
    }

    Int2 reflect(const Int2& normal) const {
        float dotProduct = static_cast<float>(dot(normal));
        return Int2(
            static_cast<int>(data[0] - 2.0f * dotProduct * normal.data[0]),
            static_cast<int>(data[1] - 2.0f * dotProduct * normal.data[1])
        );
    }

    Int2 abs() const {
        return Int2(
            std::abs(data[0]),
            std::abs(data[1])
        );
    }

    Int2 min(const Int2& other) const {
        return Int2(
            (std::min)(data[0], other.data[0]),
            (std::min)(data[1], other.data[1])
        );
    }

    Int2 max(const Int2& other) const {
        return Int2(
            (std::max)(data[0], other.data[0]),
            (std::max)(data[1], other.data[1])
        );
    }

    const int* data_ptr() const { return data; }
    int* data_ptr() { return data; }

    static Int2 Zero() { return Int2(0, 0); }
    static Int2 One() { return Int2(1, 1); }
    static Int2 UnitX() { return Int2(1, 0); }
    static Int2 UnitY() { return Int2(0, 1); }
};

std::ostream& operator<<(std::ostream& os, const Int2& vec) {
    os << "(" << vec.x() << ", " << vec.y() << ")";
    return os;
}