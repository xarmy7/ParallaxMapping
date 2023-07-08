#include "maths/maths.h"

namespace Core
{
    namespace Maths
    {
        float Fmaths::dotProduct(Core::Maths::Vec3::float3 point1, Core::Maths::Vec3::float3 point2)
        {
            float dot = (point1.x * point2.x) + (point1.y * point2.y) + (point1.z * point2.z);

            return dot;
        }

        Core::Maths::Vec3::float3 Fmaths::normal(Core::Maths::Vec3::float3 vector)
        {
            float mag = sqrtf(powf(vector.x, 2) + powf(vector.y, 2) + powf(vector.z, 2));
            return { vector.x / mag, vector.y / mag, vector.z / mag };
        }

        float Fmaths::getMin(float a, float b)
        {
            if (a < b)
                return a;

            return b;
        }

        float Fmaths::getMax(float a, float b)
        {
            if (a < b)
                return b;

            return a;
        }
    }
}