#include <immintrin.h>
#include <iostream>
#include <cmath>

class Vector2 {
private:
    alignas(16) float data[4];
public:
    //Constructors
    Vector2() {
        data[0] = 0.0f;
        data[1] = 0.0f;
        data[2] = 0.0f;
        data[3] = 0.0f;
    }
    Vector2(float xy) {
        data[0] = xy;
        data[1] = xy;
        data[2] = 0.0f;
        data[3] = 0.0f;
    }
    Vector2(float x, float y) {
        data[0] = x;
        data[1] = y;
        data[2] = 0.0f;
        data[3] = 0.0f;
    }

    Vector2(const float* arr) {
        data[0] = arr[0];
        data[1] = arr[1];
        data[2] = 0.0f;
        data[3] = 0.0f;
    };

    Vector2(const __m128& simd) {
        _mm_store_ps(data, simd);
    }

    Vector2(const Vector2& other) {
        __m128 v = _mm_load_ps(other.data);
        _mm_store_ps(data, v);
    }

    //Operators
    //+

    Vector2 operator+() const {
        return *this;
    }
    Vector2 operator+(float scalar) const {
        Vector2 result;
        __m128 a = _mm_load_ps(data);
        __m128 b = _mm_set1_ps(scalar);
        __m128 sum = _mm_add_ps(a, b);
        _mm_store_ps(result.data, sum);
        return result;
    }

    Vector2 operator+(const Vector2& other) const {
        Vector2 result;
        __m128 a = _mm_load_ps(data);
        __m128 b = _mm_load_ps(other.data);
        __m128 sum = _mm_add_ps(a, b);
        _mm_store_ps(result.data, sum);
        return result;
    }

    Vector2& operator+=(const Vector2& other) {
        __m128 a = _mm_load_ps(data);
        __m128 b = _mm_load_ps(other.data);
        __m128 sum = _mm_add_ps(a, b);
        _mm_store_ps(data, sum);
        return *this;
    }

    //-
    Vector2 operator-() const {
        return Vector2(-data[0], -data[1]);
    }

    Vector2 operator-(float scalar) const {
        Vector2 result;
        __m128 a = _mm_load_ps(data);
        __m128 b = _mm_set1_ps(scalar);
        __m128 diff = _mm_sub_ps(a, b);
        _mm_store_ps(result.data, diff);
        return result;
    }

    Vector2 operator-(const Vector2& other) const {
        Vector2 result;
        __m128 a = _mm_load_ps(data);
        __m128 b = _mm_load_ps(other.data);
        __m128 diff = _mm_sub_ps(a, b);
        _mm_store_ps(result.data, diff);
        return result;
    }

    Vector2& operator-=(const Vector2& other) {
        __m128 a = _mm_load_ps(data);
        __m128 b = _mm_load_ps(other.data);
        __m128 diff = _mm_sub_ps(a, b);
        _mm_store_ps(data, diff);
        return *this;
    }

    //*
    Vector2 operator*(float scalar) const {
        Vector2 result;
        __m128 a = _mm_load_ps(data);
        __m128 b = _mm_set1_ps(scalar);
        __m128 prod = _mm_mul_ps(a, b);
        _mm_store_ps(result.data, prod);
        return result;
    }

    Vector2 operator*(const Vector2& other) const {
        Vector2 result;
        __m128 a = _mm_load_ps(data);
        __m128 b = _mm_load_ps(other.data);
        __m128 prod = _mm_mul_ps(a, b);
        _mm_store_ps(result.data, prod);
        return result;
    }

    Vector2& operator*=(const Vector2& other) {
        __m128 a = _mm_load_ps(data);
        __m128 b = _mm_load_ps(other.data);
        __m128 prod = _mm_mul_ps(a, b);
        _mm_store_ps(data, prod);
        return *this;
    }

    // /
    Vector2 operator/(float scalar) const {
        Vector2 result;
        __m128 a = _mm_load_ps(data);
        __m128 b = _mm_set1_ps(scalar);
        __m128 quot = _mm_div_ps(a, b);
        _mm_store_ps(result.data, quot);
        return result;
    }

    Vector2 operator/(const Vector2& other) const {
        Vector2 result;
        __m128 a = _mm_load_ps(data);
        __m128 b = _mm_load_ps(other.data);
        __m128 quot = _mm_div_ps(a, b);
        _mm_store_ps(result.data, quot);
        return result;
    }

    Vector2& operator/=(const Vector2& other) {
        __m128 a = _mm_load_ps(data);
        __m128 b = _mm_load_ps(other.data);
        __m128 quot = _mm_div_ps(a, b);
        _mm_store_ps(data, quot);
        return *this;
    }

    // =

    Vector2& operator=(const Vector2& other) {
        if (this != &other) {
            data[0] = other.data[0];
            data[1] = other.data[1];
            data[2] = other.data[2];
            data[3] = other.data[3];
        }

        return *this;
    }

    bool operator==(const Vector2& other) const {
        return data[0] == other.data[0] && data[1] == other.data[1];
    }

    bool operator!=(const Vector2& other) const {
        return !(*this == other);
    }

    float& x() { return data[0]; }
    const float& x() const { return data[0]; }

    float& y() { return data[1]; }
    const float& y() const { return data[1]; }

    //util
    float length() const {
        __m128 a = _mm_load_ps(data);
        __m128 sq = _mm_mul_ps(a, a);

        float temp[4];
        _mm_store_ps(temp, sq);
        return std::sqrt(temp[0] + temp[1]);
    }

    float lengthSquared() const {
        __m128 a = _mm_load_ps(data);
        __m128 sq = _mm_mul_ps(a, a);
        float temp[4];
        _mm_store_ps(temp, sq);
        return temp[0] + temp[1];
    }

    Vector2 normalized() const {
        float len = length();
        if (len > 0.0f) {
            return *this * (1.0f / len);
        }
        return Vector2(0.0f, 0.0f);
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

    float dot(const Vector2& other) const {
        __m128 a = _mm_load_ps(data);
        __m128 b = _mm_load_ps(other.data);
        __m128 prod = _mm_mul_ps(a, b);
        float temp[4];
        _mm_store_ps(temp, prod);
        return temp[0] + temp[1];
    }

    //Setters
    void set(float newX, float newY) {
        data[0] = newX;
        data[1] = newY;
    }

    void setX(float newX) {
        data[0] = newX;
    }
    void setY(float newY) {
        data[1] = newY;
    }
    void set(const Vector2& other) {
        __m128 v = _mm_load_ps(other.data);
        _mm_store_ps(data, v);
    }

    float cross(const Vector2& other) const {
        return data[0] * other.data[1] - data[1] * other.data[0];
    }

    float distance(const Vector2& other) const {
        return (*this - other).length();
    }

    float distanceSquared(const Vector2& other) const {
        return (*this - other).lengthSquared();
    }

    Vector2 lerp(const Vector2& other, float t) const {
        return *this * (1.0f - t) + other * t;
    }

    float angle(const Vector2& other) const {
        float dotProduct = dot(other);
        float lengths = length() * other.length();
        if (lengths == 0.0f) return 0.0f;
        return std::acos(dotProduct / lengths);
    }

    Vector2 rotated(float angle) const {
        float s = std::sin(angle);
        float c = std::cos(angle);
        return Vector2(
            data[0] * c - data[1] * s,
            data[0] * s + data[1] * c
        );
    }

    Vector2 projectOnto(const Vector2& onto) const {
        float ontoLengthSq = onto.lengthSquared();
        if (ontoLengthSq == 0.0f) return Vector2::Zero();
        return onto * (dot(onto) / ontoLengthSq);
    }

    Vector2 reflect(const Vector2& normal) const {
        return *this - normal * (2.0f * dot(normal));
    }

    Vector2 abs() const {
        return Vector2(
            std::abs(data[0]),
            std::abs(data[1])
        );
    }

    Vector2 min(const Vector2& other) const {
        return Vector2(
            std::min(data[0], other.data[0]),
            std::min(data[1], other.data[1])
        );
    }

    Vector2 max(const Vector2& other) const {
        return Vector2(
            std::max(data[0], other.data[0]),
            std::max(data[1], other.data[1])
        );
    }


    const float* data_ptr() const { return data; }
    float* data_ptr() { return data; }

    //standards
    static Vector2 Zero() { return Vector2(0.0f, 0.0f); }
    static Vector2 One() { return Vector2(1.0f, 1.0f); }
    static Vector2 UnitX() { return Vector2(1.0f, 0.0f); }
    static Vector2 UnitY() { return Vector2(0.0f, 1.0f); }
};

std::ostream& operator<<(std::ostream& os, const Vector2& vec) {
    os << "(" << vec.x() << ", " << vec.y() << ")";
    return os;
}