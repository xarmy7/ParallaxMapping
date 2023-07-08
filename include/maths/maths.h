#pragma once

#include "maths/vec3.h"

#include <cmath>

namespace Core
{
    namespace Maths
    {
        class Fmaths
        {
        private:

        public:
            float dotProduct(Core::Maths::Vec3::float3 point1, Core::Maths::Vec3::float3 point2);
            static Core::Maths::Vec3::float3 normal(Core::Maths::Vec3::float3 vector);
            float getMin(float a, float b);
            float getMax(float a, float b);
        };
    }
}
