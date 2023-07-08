#include "maths/mat4.h"

using namespace Core::Maths::Mat4;

mat4x4 mat4::identity()
{
    return {
        1.f, 0.f, 0.f, 0.f,
        0.f, 1.f, 0.f, 0.f,
        0.f, 0.f, 1.f, 0.f,
        0.f, 0.f, 0.f, 1.f,
    };
}

mat4x4 mat4::perspective(float fovY, float aspect, float near, float far)
{
    float top = near * maths::tan(fovY / 2.f);
    float right = top * aspect;
    return mat4::frustum(-right, right, -top, top, near, far);
}

mat4x4 mat4::frustum(float left, float right, float bottom, float top, float near, float far)
{
    return
    {
        (near * 2.f) / (right - left),   0.f,                              0.f,                               0.f,
        0.f,                             (near * 2.f) / (top - bottom),    0.f,                               0.f,
        (right + left) / (right - left), (top + bottom) / (top - bottom), -(far + near) / (far - near),      -1.f,
        0.f,                             0.f,                             -(far * near * 2.f) / (far - near), 0.f
    };
}

mat4x4 mat4::translate(Core::Maths::Vec3::float3 pos)
{
    return {
        1.f, 0.f, 0.f, 0.f,
        0.f, 1.f, 0.f, 0.f,
        0.f, 0.f, 1.f, 0.f,
        pos.x, pos.y, pos.z, 1.f,
    };
}

mat4x4 mat4::scale(Core::Maths::Vec3::float3 s)
{
    return {
          s.x, 0.f, 0.f, 0.f,
        0.f,   s.y, 0.f, 0.f,
        0.f, 0.f,   s.z, 0.f,
        0.f, 0.f, 0.f, 1.f,
    };
}

mat4x4 mat4::rotateX(float angleRadians)
{
    float c = maths::cos(angleRadians);
    float s = maths::sin(angleRadians);

    return
    {
        1.f, 0.f, 0.f, 0.f,
        0.f,   c,   s, 0.f,
        0.f,  -s,   c, 0.f,
        0.f, 0.f, 0.f, 1.f,
    };
}

mat4x4 mat4::rotateY(float angleRadians)
{
    float c = maths::cos(angleRadians);
    float s = maths::sin(angleRadians);

    return
    {
          c, 0.f,  -s, 0.f,
        0.f, 1.f, 0.f, 0.f,
          s, 0.f,   c, 0.f,
        0.f, 0.f, 0.f, 1.f,
    };
}

mat4x4 mat4::rotateZ(float angleRadians)
{
    float c = cosf(angleRadians);
    float s = sinf(angleRadians);

    return {
           c,   s, 0.f, 0.f,
          -s,   c, 0.f, 0.f,
         0.f, 0.f, 1.f, 0.f,
         0.f, 0.f, 0.f, 1.f
    };
}

mat4x4 mat4::rotateXYZ(Core::Maths::Vec3::float3 angleRadians)
{
    return mat4::rotateX(angleRadians.x) * mat4::rotateY(angleRadians.y) * mat4::rotateZ(angleRadians.z);
}