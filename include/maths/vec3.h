#pragma once

namespace Core
{
    namespace Maths
    {
        namespace Vec3
        {
            union float3
            {
                float e[3];
                struct { float x; float y; float z; };
                struct { float r; float g; float b; };
            };

            inline float3 operator-(float3 a) { return { -a.x, -a.y, -a.z }; }
            inline float3 operator-(float3 a, float3 b) { return { a.x - b.x, a.y - b.y, a.z - b.z }; }
        }
    }
}