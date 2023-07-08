#pragma once

namespace Core
{
    namespace Maths
    {
        namespace Vec2
        {
            union float2
            {
                float e[2];
                struct { float x; float y; };
            };

            inline float2 operator-(float2 a, float2 b) { return { a.x - b.x, a.y - b.y }; }

            class vec2
            {
            };
        }
    }
}

