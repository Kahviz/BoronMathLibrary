#include <immintrin.h>
#include <iostream>
#include <cmath>

class Vector4 {
private:
    alignas(16) float data[4];
public:
    //Constructors
    Vector4() {
        data[0] = 0.0f;
        data[1] = 0.0f;
        data[2] = 0.0f;
        data[3] = 0.0f;
    }
    Vector4(float xyzw) {
        data[0] = xyzw;
        data[1] = xyzw;
        data[2] = xyzw;
        data[3] = xyzw;
    }
    Vector4(float x, float y, float z, float w) {
        data[0] = x;
        data[1] = y;
        data[2] = z;
        data[3] = w;
    }

    Vector4(const float* arr) {
        data[0] = arr[0];
        data[1] = arr[1];
        data[2] = arr[2];
        data[3] = arr[3];
    };

    Vector4(const __m128& simd) {
        _mm_store_ps(data, simd);
    }

    Vector4(const Vector4& other) {
        __m128 v = _mm_load_ps(other.data);
        _mm_store_ps(data, v);
    }

    //Operators
    //+

    Vector4 operator+() const {
        return *this;
    }

    Vector4 operator+(float scalar) const {
        Vector4 result;
        __m128 a = _mm_load_ps(data);
        __m128 b = _mm_set1_ps(scalar);
        __m128 sum = _mm_add_ps(a, b);
        _mm_store_ps(result.data, sum);
        return result;
    }

    Vector4 operator+(const Vector4& other) const {
        Vector4 result;
        __m128 a = _mm_load_ps(data);
        __m128 b = _mm_load_ps(other.data);
        __m128 sum = _mm_add_ps(a, b);
        _mm_store_ps(result.data, sum);
        return result;
    }

    Vector4& operator+=(const Vector4& other) {
        __m128 a = _mm_load_ps(data);
        __m128 b = _mm_load_ps(other.data);
        __m128 sum = _mm_add_ps(a, b);
        _mm_store_ps(data, sum);
        return *this;
    }

    //-
    Vector4 operator-() const {
        return Vector4(-data[0], -data[1], -data[2], -data[3]);
    }

    Vector4 operator-(float scalar) const {
        Vector4 result;
        __m128 a = _mm_load_ps(data);
        __m128 b = _mm_set1_ps(scalar);
        __m128 diff = _mm_sub_ps(a, b);
        _mm_store_ps(result.data, diff);
        return result;
    }

    Vector4 operator-(const Vector4& other) const {
        Vector4 result;
        __m128 a = _mm_load_ps(data);
        __m128 b = _mm_load_ps(other.data);
        __m128 diff = _mm_sub_ps(a, b);
        _mm_store_ps(result.data, diff);
        return result;
    }

    Vector4& operator-=(const Vector4& other) {
        __m128 a = _mm_load_ps(data);
        __m128 b = _mm_load_ps(other.data);
        __m128 diff = _mm_sub_ps(a, b);
        _mm_store_ps(data, diff);
        return *this;
    }

    //*
    Vector4 operator*(float scalar) const {
        Vector4 result;
        __m128 a = _mm_load_ps(data);
        __m128 b = _mm_set1_ps(scalar);
        __m128 prod = _mm_mul_ps(a, b);
        _mm_store_ps(result.data, prod);
        return result;
    }

    Vector4 operator*(const Vector4& other) const {
        Vector4 result;
        __m128 a = _mm_load_ps(data);
        __m128 b = _mm_load_ps(other.data);
        __m128 prod = _mm_mul_ps(a, b);
        _mm_store_ps(result.data, prod);
        return result;
    }

    Vector4& operator*=(const Vector4& other) {
        __m128 a = _mm_load_ps(data);
        __m128 b = _mm_load_ps(other.data);
        __m128 prod = _mm_mul_ps(a, b);
        _mm_store_ps(data, prod);
        return *this;
    }

    // /
    Vector4 operator/(float scalar) const {
        Vector4 result;
        __m128 a = _mm_load_ps(data);
        __m128 b = _mm_set1_ps(scalar);
        __m128 quot = _mm_div_ps(a, b);
        _mm_store_ps(result.data, quot);
        return result;
    }

    Vector4 operator/(const Vector4& other) const {
        Vector4 result;
        __m128 a = _mm_load_ps(data);
        __m128 b = _mm_load_ps(other.data);
        __m128 quot = _mm_div_ps(a, b);
        _mm_store_ps(result.data, quot);
        return result;
    }

    Vector4& operator/=(const Vector4& other) {
        __m128 a = _mm_load_ps(data);
        __m128 b = _mm_load_ps(other.data);
        __m128 quot = _mm_div_ps(a, b);
        _mm_store_ps(data, quot);
        return *this;
    }

    // =

    Vector4& operator=(const Vector4& other) {
        if (this != &other) {
            data[0] = other.data[0];
            data[1] = other.data[1];
            data[2] = other.data[2];
            data[3] = other.data[3];
        }

        return *this;
    }

    bool operator==(const Vector4& other) const {
        return data[0] == other.data[0] &&
            data[1] == other.data[1] &&
            data[2] == other.data[2] &&
            data[3] == other.data[3];
    }

    bool operator!=(const Vector4& other) const {
        return !(*this == other);
    }

    float& x() { return data[0]; }
    const float& x() const { return data[0]; }

    float& y() { return data[1]; }
    const float& y() const { return data[1]; }

    float& z() { return data[2]; }
    const float& z() const { return data[2]; }

    float& w() { return data[2]; }
    const float& w() const { return data[2]; }

    //util
    float length() const {
        __m128 a = _mm_load_ps(data);
        __m128 sq = _mm_mul_ps(a, a);

        float temp[4];
        _mm_store_ps(temp, sq);
        return std::sqrt(temp[0] + temp[1] + temp[2] + temp[3]);
    }

    float lengthSquared() const {
        __m128 a = _mm_load_ps(data);
        __m128 sq = _mm_mul_ps(a, a);
        float temp[4];
        _mm_store_ps(temp, sq);
        return temp[0] + temp[1] + temp[2] + temp[3];
    }

    Vector4 normalized() const {
        float len = length();
        if (len > 0.0f) {
            return *this * (1.0f / len);
        }
        return Vector4(0.0f, 0.0f, 0.0f, 0.0f);
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

    float dot(const Vector4& other) const {
        __m128 a = _mm_load_ps(data);
        __m128 b = _mm_load_ps(other.data);
        __m128 prod = _mm_mul_ps(a, b);
        float temp[4];
        _mm_store_ps(temp, prod);
        return temp[0] + temp[1] + temp[2] + temp[3];
    }

    //Setters
    void set(float newX, float newY, float newZ,float newW) {
        data[0] = newX;
        data[1] = newY;
        data[2] = newZ;
        data[3] = newW;
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
    void setW(float newW) {
        data[3] = newW;
    }


    void set(const Vector4& other) {
        __m128 v = _mm_load_ps(other.data);
        _mm_store_ps(data, v);
    }

    Vector4 cross(const Vector4& other) const {
        return Vector4(
            data[1] * other.data[2] - data[2] * other.data[1],
            data[2] * other.data[0] - data[0] * other.data[2],
            data[0] * other.data[1] - data[1] * other.data[0],
            0.0f
        );
    }

    float distance(const Vector4& other) const {
        return (*this - other).length();
    }

    float distanceSquared(const Vector4& other) const {
        return (*this - other).lengthSquared();
    }

    Vector4 lerp(const Vector4& other, float t) const {
        return *this * (1.0f - t) + other * t;
    }

    float angle(const Vector4& other) const {
        float dotProduct = dot(other);
        float lengths = length() * other.length();
        if (lengths == 0.0f) return 0.0f;
        return std::acos(dotProduct / lengths);
    }

    Vector4 rotated(float angle, const Vector4& axis) const {
        float s = std::sin(angle);
        float c = std::cos(angle);
        float oneMinusC = 1.0f - c;

        Vector4 normAxis = axis.normalized();
        float x = normAxis.x();
        float y = normAxis.y();
        float z = normAxis.z();

        return Vector4(
            data[0] * (c + x * x * oneMinusC) +
            data[1] * (x * y * oneMinusC - z * s) +
            data[2] * (x * z * oneMinusC + y * s),

            data[0] * (y * x * oneMinusC + z * s) +
            data[1] * (c + y * y * oneMinusC) +
            data[2] * (y * z * oneMinusC - x * s),

            data[0] * (z * x * oneMinusC - y * s) +
            data[1] * (z * y * oneMinusC + x * s) +
            data[2] * (c + z * z * oneMinusC),

            data[3]
        );
    }

    Vector4 rotatedX(float angle) const {
        float s = std::sin(angle);
        float c = std::cos(angle);
        return Vector4(
            data[0],
            data[1] * c - data[2] * s,
            data[1] * s + data[2] * c,
            data[3]
        );
    }

    Vector4 rotatedY(float angle) const {
        float s = std::sin(angle);
        float c = std::cos(angle);
        return Vector4(
            data[0] * c + data[2] * s,
            data[1],
            -data[0] * s + data[2] * c,
            data[3]
        );
    }

    Vector4 rotatedZ(float angle) const {
        float s = std::sin(angle);
        float c = std::cos(angle);
        return Vector4(
            data[0] * c - data[1] * s,
            data[0] * s + data[1] * c,
            data[2],
            data[3]
        );
    }

    Vector4 projectOnto(const Vector4& onto) const {
        float ontoLengthSq = onto.lengthSquared();
        if (ontoLengthSq == 0.0f) return Vector4::Zero();
        return onto * (dot(onto) / ontoLengthSq);
    }

    Vector4 reflect(const Vector4& normal) const {
        return *this - normal * (2.0f * dot(normal));
    }

    Vector4 abs() const {
        return Vector4(
            std::abs(data[0]),
            std::abs(data[1]),
            std::abs(data[2]),
            std::abs(data[3])
        );
    }

    Vector4 min(const Vector4& other) const {
        return Vector4(
            std::min(data[0], other.data[0]),
            std::min(data[1], other.data[1]),
            std::min(data[2], other.data[2]),
            std::min(data[3], other.data[3])
        );
    }

    Vector4 max(const Vector4& other) const {
        return Vector4(
            std::max(data[0], other.data[0]),
            std::max(data[1], other.data[1]),
            std::max(data[2], other.data[2]),
            std::max(data[3], other.data[3])
        );
    }

    const float* data_ptr() const { return data; }
    float* data_ptr() { return data; }

    //standards
    static Vector4 Zero() { return Vector4(0.0f, 0.0f, 0.0f, 0.0f); }
    static Vector4 One() { return Vector4(1.0f, 1.0f, 1.0f, 1.0f); }
    static Vector4 UnitX() { return Vector4(1.0f, 0.0f, 0.0f, 0.0f); }
    static Vector4 UnitY() { return Vector4(0.0f, 1.0f, 0.0f, 0.0f); }
    static Vector4 UnitZ() { return Vector4(0.0f, 0.0f, 1.0f, 0.0f); }
    static Vector4 UnitW() { return Vector4(0.0f, 0.0f, 0.0f, 1.0f); }

};

std::ostream& operator<<(std::ostream& os, const Vector4& vec) {
    os << "(" << vec.x() << ", " << vec.y() << ", " << vec.z() << ", " << vec.w() << ")";
    return os;
}