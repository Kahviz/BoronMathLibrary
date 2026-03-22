#include <immintrin.h>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstdlib>

#ifdef min
#undef min
#endif
#ifdef max
#undef max
#endif

class Color255 {
private:
    alignas(16) int data[4];

    void clamp() {
        data[0] = std::max(0, std::min(255, data[0]));
        data[1] = std::max(0, std::min(255, data[1]));
        data[2] = std::max(0, std::min(255, data[2]));
        data[3] = 0;
    }

public:
    //Constructors
    Color255() {
        data[0] = data[1] = data[2] = data[3] = 0;
    }

    Color255(int xyz) {
        data[0] = data[1] = data[2] = xyz;
        data[3] = 0;
        clamp();
    }

    Color255(int x, int y, int z) {
        data[0] = x;
        data[1] = y;
        data[2] = z;
        data[3] = 0;
        clamp();
    }

    Color255(const int* arr) {
        data[0] = arr[0];
        data[1] = arr[1];
        data[2] = arr[2];
        data[3] = 0;
        clamp();
    };

    Color255(const Color255& other) {
        __m128i v = _mm_load_si128((const __m128i*)other.data);
        _mm_store_si128((__m128i*)data, v);
    }

    int x() const { return data[0]; }
    int y() const { return data[1]; }
    int z() const { return data[2]; }

    // Operators
    Color255 operator+() const {
        return *this;
    }

    Color255 operator+(int scalar) const {
        Color255 result;
        __m128i a = _mm_load_si128((const __m128i*)data);
        __m128i b = _mm_set1_epi32(scalar);
        __m128i sum = _mm_add_epi32(a, b);
        _mm_store_si128((__m128i*)result.data, sum);
        result.clamp();
        return result;
    }

    Color255 operator+(const Color255& other) const {
        Color255 result;
        __m128i a = _mm_load_si128((const __m128i*)data);
        __m128i b = _mm_load_si128((const __m128i*)other.data);
        __m128i sum = _mm_add_epi32(a, b);
        _mm_store_si128((__m128i*)result.data, sum);
        result.clamp();
        return result;
    }

    Color255& operator+=(const Color255& other) {
        __m128i a = _mm_load_si128((const __m128i*)data);
        __m128i b = _mm_load_si128((const __m128i*)other.data);
        __m128i sum = _mm_add_epi32(a, b);
        _mm_store_si128((__m128i*)data, sum);
        clamp();
        return *this;
    }

    //-
    Color255 operator-() const {
        return Color255(-data[0], -data[1], -data[2]);
    }

    Color255 operator-(int scalar) const {
        Color255 result;
        __m128i a = _mm_load_si128((const __m128i*)data);
        __m128i b = _mm_set1_epi32(scalar);
        __m128i diff = _mm_sub_epi32(a, b);
        _mm_store_si128((__m128i*)result.data, diff);
        result.clamp();
        return result;
    }

    Color255 operator-(const Color255& other) const {
        Color255 result;
        __m128i a = _mm_load_si128((const __m128i*)data);
        __m128i b = _mm_load_si128((const __m128i*)other.data);
        __m128i diff = _mm_sub_epi32(a, b);
        _mm_store_si128((__m128i*)result.data, diff);
        result.clamp();
        return result;
    }

    Color255& operator-=(const Color255& other) {
        __m128i a = _mm_load_si128((const __m128i*)data);
        __m128i b = _mm_load_si128((const __m128i*)other.data);
        __m128i diff = _mm_sub_epi32(a, b);
        _mm_store_si128((__m128i*)data, diff);
        clamp();
        return *this;
    }

    //*
    Color255 operator*(int scalar) const {
        Color255 result;
        result.data[0] = data[0] * scalar;
        result.data[1] = data[1] * scalar;
        result.data[2] = data[2] * scalar;
        result.data[3] = 0;
        result.clamp();
        return result;
    }

    Color255 operator*(float scalar) const {
        Color255 result;
        __m128 a = _mm_cvtepi32_ps(_mm_load_si128((const __m128i*)data));
        __m128 b = _mm_set1_ps(scalar);
        __m128 prod = _mm_mul_ps(a, b);
        __m128i prod_int = _mm_cvtps_epi32(prod);
        _mm_store_si128((__m128i*)result.data, prod_int);
        result.clamp();
        return result;
    }

    Color255 operator*(const Color255& other) const {
        Color255 result;
        __m128i a = _mm_load_si128((const __m128i*)data);
        __m128i b = _mm_load_si128((const __m128i*)other.data);
        __m128i prod = _mm_mullo_epi32(a, b);
        _mm_store_si128((__m128i*)result.data, prod);
        result.clamp();
        return result;
    }

    Color255& operator*=(const Color255& other) {
        __m128i a = _mm_load_si128((const __m128i*)data);
        __m128i b = _mm_load_si128((const __m128i*)other.data);
        __m128i prod = _mm_mullo_epi32(a, b);
        _mm_store_si128((__m128i*)data, prod);
        clamp();
        return *this;
    }

    // /
    Color255 operator/(int scalar) const {
        if (scalar == 0) return Color255(0, 0, 0);
        Color255 result;
        result.data[0] = data[0] / scalar;
        result.data[1] = data[1] / scalar;
        result.data[2] = data[2] / scalar;
        result.data[3] = 0;
        result.clamp();
        return result;
    }

    Color255 operator/(float scalar) const {
        if (scalar == 0.0f) return Color255(0, 0, 0);
        Color255 result;
        __m128 a = _mm_cvtepi32_ps(_mm_load_si128((const __m128i*)data));
        __m128 b = _mm_set1_ps(scalar);
        __m128 quot = _mm_div_ps(a, b);
        __m128i quot_int = _mm_cvtps_epi32(quot);
        _mm_store_si128((__m128i*)result.data, quot_int);
        result.clamp();
        return result;
    }

    Color255 operator/(const Color255& other) const {
        Color255 result;
        for (int i = 0; i < 3; i++) {
            if (other.data[i] != 0) {
                result.data[i] = data[i] / other.data[i];
            }
            else {
                result.data[i] = 255;
            }
        }
        result.data[3] = 0;
        result.clamp();
        return result;
    }

    Color255& operator/=(const Color255& other) {
        for (int i = 0; i < 3; i++) {
            if (other.data[i] != 0) {
                data[i] /= other.data[i];
            }
            else {
                data[i] = 255;
            }
        }
        data[3] = 0;
        clamp();
        return *this;
    }

    Color255& operator=(const Color255& other) {
        if (this != &other) {
            __m128i v = _mm_load_si128((const __m128i*)other.data);
            _mm_store_si128((__m128i*)data, v);
        }
        return *this;
    }

    bool operator==(const Color255& other) const {
        return data[0] == other.data[0] &&
            data[1] == other.data[1] &&
            data[2] == other.data[2];
    }

    bool operator!=(const Color255& other) const {
        return !(*this == other);
    }

    // Util
    float length() const {
        __m128i int_vec = _mm_load_si128((const __m128i*)data);
        __m128 a = _mm_cvtepi32_ps(int_vec);
        __m128 sq = _mm_mul_ps(a, a);

        __m128 sum = _mm_add_ps(sq, _mm_shuffle_ps(sq, sq, _MM_SHUFFLE(1, 0, 3, 2)));
        sum = _mm_add_ps(sum, _mm_shuffle_ps(sum, sum, _MM_SHUFFLE(2, 3, 0, 1)));
        float result;
        _mm_store_ss(&result, sum);
        return std::sqrt(result);
    }

    float lengthSquared() const {
        __m128i a = _mm_load_si128((const __m128i*)data);
        __m128 a_float = _mm_cvtepi32_ps(a);
        __m128 sq = _mm_mul_ps(a_float, a_float);

        __m128 sum = _mm_add_ps(sq, _mm_shuffle_ps(sq, sq, _MM_SHUFFLE(1, 0, 3, 2)));
        sum = _mm_add_ps(sum, _mm_shuffle_ps(sum, sum, _MM_SHUFFLE(2, 3, 0, 1)));
        float result;
        _mm_store_ss(&result, sum);
        return result;
    }

    void normalize() {
        float len = length();
        if (len > 0.0f) {
            float invLen = 1.0f / len;
            __m128i a = _mm_load_si128((const __m128i*)data);
            __m128 a_float = _mm_cvtepi32_ps(a);
            __m128 inv = _mm_set1_ps(invLen);
            __m128 norm_float = _mm_mul_ps(a_float, inv);
            __m128i norm_int = _mm_cvtps_epi32(norm_float);
            _mm_store_si128((__m128i*)data, norm_int);
            clamp();
        }
    }

    int dot(const Color255& other) const {
        __m128i a = _mm_load_si128((const __m128i*)data);
        __m128i b = _mm_load_si128((const __m128i*)other.data);
        __m128i prod = _mm_mullo_epi32(a, b);

        int temp[4];
        _mm_store_si128((__m128i*)temp, prod);
        return temp[0] + temp[1] + temp[2];
    }

    // Setters
    void set(int newX, int newY, int newZ) {
        data[0] = newX;
        data[1] = newY;
        data[2] = newZ;
        data[3] = 0;
        clamp();
    }

    void set(const Color255& other) {
        __m128i v = _mm_load_si128((const __m128i*)other.data);
        _mm_store_si128((__m128i*)data, v);
    }

    Color255 cross(const Color255& other) const {
        return Color255(
            data[1] * other.data[2] - data[2] * other.data[1],
            data[2] * other.data[0] - data[0] * other.data[2],
            data[0] * other.data[1] - data[1] * other.data[0]
        );
    }

    float distance(const Color255& other) const {
        return (*this - other).length();
    }

    float distanceSquared(const Color255& other) const {
        return (*this - other).lengthSquared();
    }

    Color255 lerp(const Color255& other, float t) const {
        return *this * (1.0f - t) + other * t;
    }

    float angle(const Color255& other) const {
        float dotProduct = static_cast<float>(dot(other));
        float lengths = length() * other.length();
        if (lengths < 1e-6f) return 0.0f;
        return std::acos(dotProduct / lengths);
    }

    __m128 to_float() const {
        return _mm_cvtepi32_ps(_mm_load_si128((const __m128i*)data));
    }

    Color255 projectOnto(const Color255& onto) const {
        float ontoLengthSq = onto.lengthSquared();
        if (ontoLengthSq < 1e-6f) return Color255::Zero();
        float scale = dot(onto) / ontoLengthSq;
        return onto * scale;
    }

    Color255 reflect(const Color255& normal) const {
        return *this - normal * (2.0f * dot(normal));
    }

    Color255 abs() const {
        return Color255(
            std::abs(data[0]),
            std::abs(data[1]),
            std::abs(data[2])
        );
    }

    Color255 min(const Color255& other) const {
        return Color255(
            std::min(data[0], other.data[0]),
            std::min(data[1], other.data[1]),
            std::min(data[2], other.data[2])
        );
    }

    Color255 max(const Color255& other) const {
        return Color255(
            std::max(data[0], other.data[0]),
            std::max(data[1], other.data[1]),
            std::max(data[2], other.data[2])
        );
    }

    const int* data_ptr() const { return data; }
    int* data_ptr() { return data; }

    // Static methods
    static Color255 Zero() { return Color255(0, 0, 0); }
    static Color255 One() { return Color255(255, 255, 255); }
    static Color255 UnitX() { return Color255(255, 0, 0); }
    static Color255 UnitY() { return Color255(0, 255, 0); }
    static Color255 UnitZ() { return Color255(0, 0, 255); }
};

std::ostream& operator<<(std::ostream& os, const Color255& vec) {
    os << "(" << vec.x() << ", " << vec.y() << ", " << vec.z() << ")";
    return os;
}