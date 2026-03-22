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
    //Constructors
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
    };

    Int3(const Int3& other) {
        __m128i v = _mm_load_si128((__m128i*)other.data);
        _mm_store_si128((__m128i*)data, v);
    }

    //Operators
    //+

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

    Int3 operator+=(const Int3& other) const {
        Int3 result;
        __m128i a = _mm_load_si128((__m128i*)data);
        __m128i b = _mm_set1_epi32(*other.data);
        __m128i diff = _mm_add_epi32(a, b);
        _mm_store_si128((__m128i*)result.data, diff);
        return result;
    }

    //-
    Int3 operator-() const {
        return Int3(-data[0], -data[1], -data[2]);
    }

    Int3 operator-(int scalar) const {
        Int3 result;
        __m128i a = _mm_load_si128((__m128i*)data);
        __m128i b = _mm_set1_epi32(scalar);
        __m128i sum = _mm_sub_epi32(a, b);
        _mm_store_si128((__m128i*)result.data, sum);
        return result;
    }

    Int3 operator-(const Int3& other) const {
        Int3 result;
        __m128i a = _mm_load_si128((__m128i*)data);
        __m128i b = _mm_set1_epi32(*other.data);
        __m128i sum = _mm_sub_epi32(a, b);
        _mm_store_si128((__m128i*)result.data, sum);
        return result;
    }

    Int3& operator-=(const Int3& other) {
        Int3 result;
        __m128i a = _mm_load_si128((__m128i*)data);
        __m128i b = _mm_set1_epi32(*other.data);
        __m128i diff = _mm_sub_epi32(a, b);
        _mm_store_si128((__m128i*)result.data, diff);
        return result;
    }

    //*
    Int3 operator*(float scalar) const {
        Int3 result;
        __m128i a = _mm_load_si128((__m128i*)data);
        __m128i b = _mm_set1_epi32(scalar);
        __m128i prod = _mm_mul_epi32(a, b);
        _mm_store_si128((__m128i*)result.data, prod);
        return result;
    }

    Int3 operator*(const Int3& other) const {
        Int3 result;
        __m128i a = _mm_load_si128((__m128i*)data);
        __m128i b = _mm_set1_epi32(*other.data);
        __m128i prod = _mm_mul_epi32(a, b);
        _mm_store_si128((__m128i*)result.data, prod);
        return result;
    }

    Int3& operator*=(const Int3& other) {
        Int3 result;
        __m128i a = _mm_load_si128((__m128i*)data);
        __m128i b = _mm_set1_epi32(*other.data);
        __m128i diff = _mm_mul_epi32(a, b);
        _mm_store_si128((__m128i*)result.data, diff);
        return result;
    }

    // /
    Int3 operator/(float scalar) const {
        Int3 result;
        __m128i a = _mm_load_si128((__m128i*)data);
        __m128i b = _mm_set1_epi32(scalar);
        __m128i quot = _mm_div_epi32(a, b);
        _mm_store_si128((__m128i*)result.data, quot);
        return result;
    }

    Int3 operator/(const Int3& other) const {
        Int3 result;
        __m128i a = _mm_load_si128((__m128i*)data);
        __m128i b = _mm_set1_epi32(*other.data);
        __m128i quot = _mm_div_epi32(a, b);
        _mm_store_si128((__m128i*)result.data, quot);
        return result;
    }

    Int3& operator/=(const Int3& other) {
        Int3 result;
        __m128i a = _mm_load_si128((__m128i*)data);
        __m128i b = _mm_set1_epi32(*other.data);
        __m128i quot = _mm_div_epi32(a, b);
        _mm_store_si128((__m128i*)result.data, quot);
        return *this;
    }

    // =

    Int3& operator=(const Int3& other) {
        if (this != &other) {
            data[0] = other.data[0];
            data[1] = other.data[1];
            data[2] = other.data[2];
            data[3] = other.data[3];
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

    float x() const { return data[0]; }
    float y() const { return data[1]; }
    float z() const { return data[2]; }

    //util
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

    void normalize() {
        float len = length();
        if (len > 0.0f) {
            float invLen = 1.0f / len;

            __m128i a = _mm_load_si128((__m128i*)data);

            __m128 a_float = _mm_cvtepi32_ps(a);

            __m128 inv = _mm_set1_ps(invLen);
            __m128 norm_float = _mm_mul_ps(a_float, inv);

            __m128i norm_int = _mm_cvtps_epi32(norm_float);

            _mm_store_si128((__m128i*)data, norm_int);
        }
    }

    int dot(const Int3& other) const {
        __m128i a = _mm_load_si128((__m128i*)data);
        __m128i b = _mm_load_si128((__m128i*)other.data);

        __m128i prod = _mm_mullo_epi32(a, b);

        int temp[4];
        _mm_store_si128((__m128i*)temp, prod);

        return temp[0] + temp[1] + temp[2];
    }

    //Setters
    void set(float newX, float newY, float newZ) {
        data[0] = newX;
        data[1] = newY;
        data[2] = newZ;
    }

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
        return *this * (1.0f - t) + other * t;
    }

    float angle(const Int3& other) const {
        float dotProduct = dot(other);
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
        return onto * (dot(onto) / ontoLengthSq);
    }

    Int3 reflect(const Int3& normal) const {
        return *this - normal * (2.0f * dot(normal));
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
            std::min(data[0], other.data[0]),
            std::min(data[1], other.data[1]),
            std::min(data[2], other.data[2])
        );
    }

    Int3 max(const Int3& other) const {
        return Int3(
            std::max(data[0], other.data[0]),
            std::max(data[1], other.data[1]),
            std::max(data[2], other.data[2])
        );
    }

    const int* data_ptr() const { return data; }
    int* data_ptr() { return data; }

    //standards
    static Int3 Zero() { return Int3(0.0f, 0.0f, 0.0f); }
    static Int3 One() { return Int3(1.0f, 1.0f, 1.0f); }
    static Int3 UnitX() { return Int3(1.0f, 0.0f, 0.0f); }
    static Int3 UnitY() { return Int3(0.0f, 1.0f, 0.0f); }
    static Int3 UnitZ() { return Int3(0.0f, 0.0f, 1.0f); }
};

std::ostream& operator<<(std::ostream& os, const Int3& vec) {
    os << "(" << vec.x() << ", " << vec.y() << ", " << vec.z() << ")";
    return os;
}