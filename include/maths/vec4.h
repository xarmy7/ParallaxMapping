#pragma once

#include "maths/vec3.h"

namespace Core
{
    namespace Maths
    {
        namespace Vec4
        {
            union float4
            {
                float4() = default;
                float4(float x, float y, float z, float w)
                    : x(x), y(y), z(z), w(w)
                {}
                float4(Core::Maths::Vec3::float3 xyz, float w)
                    : x(xyz.x), y(xyz.y), z(xyz.z), w(w)
                {}

                float e[4];
                struct { float x; float y; float z; float w; };
                struct { float r; float g; float b; float a; };
                Core::Maths::Vec3::float3 xyz;
            };

            class vec4
            {
            };
        }
    }
}

