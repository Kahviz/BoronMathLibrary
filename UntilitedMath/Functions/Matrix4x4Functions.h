#pragma once
#include "../SIMD/Vector3/Vector3.h"
#include "../SIMD/Matrix4x4/Matrix4x4.h"

#ifndef NOMINMAX
#define NOMINMAX
#endif


Matrix4x4 Matrix4x4LookAtRH(const Vector3& eye, const Vector3& target, const Vector3& worldUp) {
    Vector3 zaxis = Vector3(
        target.x() - eye.x()
    );

    zaxis.normalize();

    Vector3 xaxis = zaxis.cross(worldUp);
    xaxis.normalize();

    Vector3 yaxis = xaxis.cross(zaxis);
    yaxis.normalize();

    Matrix4x4 result;

    result(0, 0) = xaxis.x(); result(0, 1) = xaxis.y(); result(0, 2) = xaxis.z();
    result(0, 3) = -xaxis.dot(eye);

    result(1, 0) = yaxis.x(); result(1, 1) = yaxis.y(); result(1, 2) = yaxis.z();
    result(1, 3) = -yaxis.dot(eye);

    result(2, 0) = -zaxis.x(); result(2, 1) = -zaxis.y(); result(2, 2) = -zaxis.z();
    result(2, 3) = zaxis.dot(eye);

    result(3, 0) = 0.0f; result(3, 1) = 0.0f; result(3, 2) = 0.0f; result(3, 3) = 1.0f;

    return result;
}

Matrix4x4 Matrix4x4LookAtLH(const Vector3& eye, const Vector3& target, const Vector3& worldUp) {
    Vector3 zaxis = target - eye;
    zaxis.normalize();

    Vector3 xaxis = worldUp.cross(zaxis);
    xaxis.normalize();

    Vector3 yaxis = zaxis.cross(xaxis);
    yaxis.normalize();

    Matrix4x4 result;

    result(0, 0) = xaxis.x(); result(0, 1) = xaxis.y(); result(0, 2) = xaxis.z();
    result(0, 3) = -xaxis.dot(eye);

    result(1, 0) = yaxis.x(); result(1, 1) = yaxis.y(); result(1, 2) = yaxis.z();
    result(1, 3) = -yaxis.dot(eye);

    result(2, 0) = zaxis.x(); result(2, 1) = zaxis.y(); result(2, 2) = zaxis.z();
    result(2, 3) = -zaxis.dot(eye);

    result(3, 0) = 0.0f; result(3, 1) = 0.0f; result(3, 2) = 0.0f; result(3, 3) = 1.0f;

    return result;
}

Matrix4x4 Matrix4x4PerspectiveFovLH(float fovRadians, float aspect, float nearZ, float farZ) {
    float f = 1.0f / tanf(fovRadians / 2.0f);

    Matrix4x4 m = {};

    m(0, 0) = f / aspect;
    m(1, 1) = f;
    m(2, 2) = farZ / (farZ - nearZ);
    m(2, 3) = 1.0f;
    m(3, 2) = -nearZ * farZ / (farZ - nearZ);

    return m;
}

Matrix4x4 Matrix4x4PerspectiveFovRH(float fovRadians, float aspect, float nearZ, float farZ) {
    float f = 1.0f / tanf(fovRadians / 2.0f);

    Matrix4x4 m = {};

    m(0, 0) = f / aspect;
    m(1, 1) = f;
    m(2, 2) = farZ / (nearZ - farZ);
    m(2, 3) = -1.0f;
    m(3, 2) = (nearZ * farZ) / (nearZ - farZ);

    return m;
}

