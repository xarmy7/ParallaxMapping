#include <cmath>

#include "maths/vec3.h"
#include "maths/vec4.h"

#pragma once

using namespace Core::Maths::Vec3;
using namespace Core::Maths::Vec4;

namespace Core
{
    namespace Maths
    {
        namespace Mat4
        {
            union mat4x4
            {
                float e[16];
                float4 c[4];
            };

            namespace maths
            {
                const float TAU = 6.283185307179586476925f;

                inline float cos(float x) { return cosf(x); }
                inline float sin(float x) { return sinf(x); }
                inline float tan(float x) { return tanf(x); }

                inline float toRadians(float degrees) { return degrees * TAU / 360.f; }
            }

            namespace mat4
            {
                mat4x4 identity();
                mat4x4 perspective(float fovY, float aspect, float near, float far);
                mat4x4 frustum(float left, float right, float bottom, float top, float near, float far);
                mat4x4 translate(float3 pos);
                mat4x4 scale(float3 s);
                mat4x4 rotateX(float angleRadians);
                mat4x4 rotateY(float angleRadians);
                mat4x4 rotateZ(float angleRadians);
                mat4x4 rotateXYZ(float3 angleRadians);
            }

            inline mat4x4 operator*(const mat4x4& a, const mat4x4& b)
            {
                mat4x4 res = {};
                for (int c = 0; c < 4; ++c)
                    for (int r = 0; r < 4; ++r)
                        for (int i = 0; i < 4; ++i)
                            res.c[c].e[r] += a.c[i].e[r] * b.c[c].e[i];
                return res;
            }

            inline mat4x4& operator*=(mat4x4& a, const mat4x4& b)
            {
                a = a * b;
                return a;
            }
        }
    }
}
