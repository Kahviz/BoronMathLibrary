#pragma once

#include <immintrin.h>
#include <iostream>
#include <cmath>
#include "../Matrix4x4/Matrix4x4.h"
#include <algorithm>
#include <cstdlib>

#ifndef NOMINMAX
#define NOMINMAX
#endif

class Vector3 {
private:
    alignas(16) float data[4];
public:
    //Constructors
    Vector3() {
        data[0] = 0.0f;
        data[1] = 0.0f;
        data[2] = 0.0f;
        data[3] = 0.0f;
    }
    Vector3(float xyz) {
        data[0] = xyz;
        data[1] = xyz;
        data[2] = xyz;
        data[3] = 0.0f;
    }
    Vector3(float x, float y,float z) {
        data[0] = x;
        data[1] = y;
        data[2] = z;
        data[3] = 0.0f;
    }

    Vector3(const float* arr) {
        data[0] = arr[0];
        data[1] = arr[1];
        data[2] = arr[2];
        data[3] = 0.0f;
    };

    Vector3(const __m128& simd) {
        _mm_store_ps(data, simd);
    }

    Vector3(const Vector3& other) {
        __m128 v = _mm_load_ps(other.data);
        _mm_store_ps(data, v);
    }

    //Operators
    //+

    Vector3 operator+() const {
        return *this;
    }

    Vector3 operator+(float scalar) const {
        Vector3 result;
        __m128 a = _mm_load_ps(data);
        __m128 b = _mm_set1_ps(scalar);
        __m128 sum = _mm_add_ps(a, b);
        _mm_store_ps(result.data, sum);
        return result;
    }

    Vector3 operator+(const Vector3& other) const {
        Vector3 result;
        __m128 a = _mm_load_ps(data);
        __m128 b = _mm_load_ps(other.data);
        __m128 sum = _mm_add_ps(a, b);
        _mm_store_ps(result.data, sum);
        return result;
    }

    Vector3& operator+=(const Vector3& other) {
        __m128 a = _mm_load_ps(data);
        __m128 b = _mm_load_ps(other.data);
        __m128 sum = _mm_add_ps(a, b);
        _mm_store_ps(data, sum);
        return *this;
    }

    //-
    Vector3 operator-() const {
        return Vector3(-data[0], -data[1], -data[2]);
    }

    Vector3 operator-(float scalar) const {
        Vector3 result;
        __m128 a = _mm_load_ps(data);
        __m128 b = _mm_set1_ps(scalar);
        __m128 diff = _mm_sub_ps(a, b);
        _mm_store_ps(result.data, diff);
        return result;
    }

    Vector3 operator-(const Vector3& other) const {
        Vector3 result;
        __m128 a = _mm_load_ps(data);
        __m128 b = _mm_load_ps(other.data);
        __m128 diff = _mm_sub_ps(a, b);
        _mm_store_ps(result.data, diff);
        return result;
    }

    Vector3& operator-=(const Vector3& other) {
        __m128 a = _mm_load_ps(data);
        __m128 b = _mm_load_ps(other.data);
        __m128 diff = _mm_sub_ps(a, b);
        _mm_store_ps(data, diff);
        return *this;
    }

    //*
    Vector3 operator*(float scalar) const {
        Vector3 result;
        __m128 a = _mm_load_ps(data);
        __m128 b = _mm_set1_ps(scalar);
        __m128 prod = _mm_mul_ps(a, b);
        _mm_store_ps(result.data, prod);
        return result;
    }

    Vector3 operator*(const Vector3& other) const {
        Vector3 result;
        __m128 a = _mm_load_ps(data);
        __m128 b = _mm_load_ps(other.data);
        __m128 prod = _mm_mul_ps(a, b);
        _mm_store_ps(result.data, prod);
        return result;
    }

    Vector3& operator*=(const Vector3& other) {
        __m128 a = _mm_load_ps(data);
        __m128 b = _mm_load_ps(other.data);
        __m128 prod = _mm_mul_ps(a, b);
        _mm_store_ps(data, prod);
        return *this;
    }

    // /
    Vector3 operator/(float scalar) const {
        Vector3 result;
        __m128 a = _mm_load_ps(data);
        __m128 b = _mm_set1_ps(scalar);
        __m128 quot = _mm_div_ps(a, b);
        _mm_store_ps(result.data, quot);
        return result;
    }

    Vector3 operator/(const Vector3& other) const {
        Vector3 result;
        __m128 a = _mm_load_ps(data);
        __m128 b = _mm_load_ps(other.data);
        __m128 quot = _mm_div_ps(a, b);
        _mm_store_ps(result.data, quot);
        return result;
    }

    Vector3& operator/=(const Vector3& other) {
        __m128 a = _mm_load_ps(data);
        __m128 b = _mm_load_ps(other.data);
        __m128 quot = _mm_div_ps(a, b);
        _mm_store_ps(data, quot);
        return *this;
    }

    // =

    Vector3& operator=(const Vector3& other) {
        if (this != &other) {
            data[0] = other.data[0];
            data[1] = other.data[1];
            data[2] = other.data[2];
            data[3] = other.data[3];
        }

        return *this;
    }

    bool operator==(const Vector3& other) const {
        return data[0] == other.data[0] &&
            data[1] == other.data[1] &&
            data[2] == other.data[2];
    }

    bool operator!=(const Vector3& other) const {
        return !(*this == other);
    }

    float& x() { return data[0]; }
    const float& x() const { return data[0]; }

    float& y() { return data[1]; }
    const float& y() const { return data[1]; }

    float& z() { return data[2]; }
    const float& z() const { return data[2]; }

    //util
    float length() const {
        __m128 a = _mm_load_ps(data);
        __m128 sq = _mm_mul_ps(a, a);

        float temp[4];
        _mm_store_ps(temp, sq);
        return std::sqrt(temp[0] + temp[1] + temp[2]);
    }

    float lengthSquared() const {
        __m128 a = _mm_load_ps(data);
        __m128 sq = _mm_mul_ps(a, a);
        float temp[4];
        _mm_store_ps(temp, sq);
        return temp[0] + temp[1] + temp[2];
    }

    Vector3 normalized() const {
        float len = length();
        if (len > 0.0f) {
            return *this * (1.0f / len);
        }
        return Vector3(0.0f, 0.0f,0.0f);
    }

    void normalize() {
        float len = length();
        if (len > 0.0f) {
            float invLen = 1.0f / len;
            __m128 a = _mm_load_ps(data);
            __m128 b = _mm_set1_ps(invLen);
            __m128 norm = _mm_mul_ps(a, b);
            _mm_store_ps(data, norm);
        }
    }

    float dot(const Vector3& other) const {
        __m128 a = _mm_load_ps(data);
        __m128 b = _mm_load_ps(other.data);
        __m128 prod = _mm_mul_ps(a, b);
        float temp[4];
        _mm_store_ps(temp, prod);
        return temp[0] + temp[1] + temp[2];
    }

    //Setters
    void set(float newX, float newY,float newZ) {
        data[0] = newX;
        data[1] = newY;
        data[2] = newZ;
    }

    void setX(float newX) {
        data[0] = newX;
    }
    void setY(float newY) {
        data[1] = newY;
    }
    void setZ(float newZ) {
        data[2] = newZ;
    }

    void set(const Vector3& other) {
        __m128 v = _mm_load_ps(other.data);
        _mm_store_ps(data, v);
    }

    Vector3 cross(const Vector3& other) const {
        return Vector3(
            data[1] * other.data[2] - data[2] * other.data[1],
            data[2] * other.data[0] - data[0] * other.data[2],
            data[0] * other.data[1] - data[1] * other.data[0]
        );
    }

    float distance(const Vector3& other) const {
        return (*this - other).length();
    }

    float distanceSquared(const Vector3& other) const {
        return (*this - other).lengthSquared();
    }

    Vector3 lerp(const Vector3& other, float t) const {
        return *this * (1.0f - t) + other * t;
    }

    float angle(const Vector3& other) const {
        float dotProduct = dot(other);
        float lengths = length() * other.length();
        if (lengths == 0.0f) return 0.0f;
        return std::acos(dotProduct / lengths);
    }

    Vector3 rotated(float angle, const Vector3& axis) const {
        float s = std::sin(angle);
        float c = std::cos(angle);
        float oneMinusC = 1.0f - c;

        Vector3 normAxis = axis.normalized();
        float x = normAxis.x();
        float y = normAxis.y();
        float z = normAxis.z();

        return Vector3(
            data[0] * (c + x * x * oneMinusC) +
            data[1] * (x * y * oneMinusC - z * s) +
            data[2] * (x * z * oneMinusC + y * s),

            data[0] * (y * x * oneMinusC + z * s) +
            data[1] * (c + y * y * oneMinusC) +
            data[2] * (y * z * oneMinusC - x * s),

            data[0] * (z * x * oneMinusC - y * s) +
            data[1] * (z * y * oneMinusC + x * s) +
            data[2] * (c + z * z * oneMinusC)
        );
    }

    Vector3 rotatedX(float angle) const {
        float s = std::sin(angle);
        float c = std::cos(angle);
        return Vector3(
            data[0],
            data[1] * c - data[2] * s,
            data[1] * s + data[2] * c
        );
    }

    Vector3 rotatedY(float angle) const {
        float s = std::sin(angle);
        float c = std::cos(angle);
        return Vector3(
            data[0] * c + data[2] * s,
            data[1],
            -data[0] * s + data[2] * c
        );
    }

    Vector3 rotatedZ(float angle) const {
        float s = std::sin(angle);
        float c = std::cos(angle);
        return Vector3(
            data[0] * c - data[1] * s,
            data[0] * s + data[1] * c,
            data[2]
        );
    }

    Vector3 projectOnto(const Vector3& onto) const {
        float ontoLengthSq = onto.lengthSquared();
        if (ontoLengthSq == 0.0f) return Vector3::Zero();
        return onto * (dot(onto) / ontoLengthSq);
    }

    Vector3 reflect(const Vector3& normal) const {
        return *this - normal * (2.0f * dot(normal));
    }

    Vector3 abs() const {
        return Vector3(
            std::abs(data[0]),
            std::abs(data[1]),
            std::abs(data[2])
        );
    }

    Vector3 min(const Vector3& other) const {
        return Vector3(
            std::min(data[0], other.data[0]),
            std::min(data[1], other.data[1]),
            std::min(data[2], other.data[2])
        );
    }

    Vector3 max(const Vector3& other) const {
        return Vector3(
            std::max(data[0], other.data[0]),
            std::max(data[1], other.data[1]),
            std::max(data[2], other.data[2])
        );
    }

    const float* data_ptr() const { return data; }
    float* data_ptr() { return data; }

    //standards
    static Vector3 Zero() { return Vector3(0.0f, 0.0f,0.0f); }
    static Vector3 One() { return Vector3(1.0f, 1.0f,1.0f); }
    static Vector3 UnitX() { return Vector3(1.0f, 0.0f,0.0f); }
    static Vector3 UnitY() { return Vector3(0.0f, 1.0f,0.0f); }
    static Vector3 UnitZ() { return Vector3(0.0f, 0.0f, 1.0f); }

    inline Vector3 Vector3TransformCoord(const Vector3& v, const Matrix4x4& m) {
        float x = v.x();
        float y = v.y();
        float z = v.z();

        float resultX = m(0, 0) * x + m(0, 1) * y + m(0, 2) * z + m(0, 3);
        float resultY = m(1, 0) * x + m(1, 1) * y + m(1, 2) * z + m(1, 3);
        float resultZ = m(2, 0) * x + m(2, 1) * y + m(2, 2) * z + m(2, 3);
        float resultW = m(3, 0) * x + m(3, 1) * y + m(3, 2) * z + m(3, 3);

        if (resultW != 0.0f && resultW != 1.0f) {
            float invW = 1.0f / resultW;
            resultX *= invW;
            resultY *= invW;
            resultZ *= invW;
        }

        return Vector3(resultX, resultY, resultZ);
    }
};

std::ostream& operator<<(std::ostream& os, const Vector3& vec) {
    os << "(" << vec.x() << ", " << vec.y() << ", " << vec.z() << ")";
    return os;
}
