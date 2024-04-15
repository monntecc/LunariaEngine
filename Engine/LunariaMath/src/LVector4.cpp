/*
 * @copyright Copyright(c) 2024 Vladyslav Potapenko. All rights reserved.
 * @license Licensed under the MIT License. See LICENSE in the project root for license information.
 */

#include <utility>
#include <stdexcept>

#include "LunariaMath/LVector4.hpp"

namespace Lunaria::Math {

    const LVector4 LVector4::One(1.0f, 1.0f, 1.0f, 1.0f);
    const LVector4 LVector4::Zero(0.0f, 0.0f, 0.0f, 0.0f);

    LVector4::LVector4(float p_x, float p_y, float p_z, float p_w) : x(p_x), y(p_y), z(p_z), w(p_w)
    {
    }

    LVector4::LVector4(const LVector4& p_vector, float p_w) : x(p_vector.x), y(p_vector.y), z(p_vector.z), w(p_w)
    {
    }

    LVector4 LVector4::operator-() const
    {
        return operator*(-1);
    }

    LVector4& LVector4::operator=(const LVector4& p_other) = default;

    LVector4 LVector4::operator+(const LVector4& p_other) const
    {
        return Add(*this, p_other);
    }

    LVector4& LVector4::operator+=(const LVector4& p_other)
    {
        *this = Add(*this, p_other);
        return *this;
    }

    LVector4 LVector4::operator-(const LVector4& p_other) const
    {
        return Substract(*this, p_other);
    }

    LVector4& LVector4::operator-=(const LVector4& p_other)
    {
        *this = Substract(*this, p_other);
        return *this;
    }

    LVector4 LVector4::operator*(float p_scalar) const
    {
        return Multiply(*this, p_scalar);
    }

    LVector4& LVector4::operator*=(float p_scalar)
    {
        *this = Multiply(*this, p_scalar);
        return *this;
    }

    LVector4 LVector4::operator/(float p_scalar) const
    {
        return Divide(*this, p_scalar);
    }

    LVector4& LVector4::operator/=(float p_scalar)
    {
        *this = Divide(*this, p_scalar);
        return *this;
    }

    bool LVector4::operator==(const LVector4& p_other) const
    {
        return
            this->x == p_other.x &&
            this->y == p_other.y &&
            this->z == p_other.z &&
            this->w == p_other.w;
    }

    bool LVector4::operator!=(const LVector4& p_other) const
    {
        return !operator==(p_other);
    }

    LVector4 LVector4::Add(const LVector4& p_left, const LVector4& p_right)
    {
        return LVector4
        (
            p_left.x + p_right.x,
            p_left.y + p_right.y,
            p_left.z + p_right.z,
            p_left.w + p_right.w
        );
    }

    LVector4 LVector4::Substract(const LVector4& p_left, const LVector4& p_right)
    {
        return LVector4
        (
            p_left.x - p_right.x,
            p_left.y - p_right.y,
            p_left.z - p_right.z,
            p_left.w - p_right.w
        );
    }

    LVector4 LVector4::Multiply(const LVector4& p_target, float p_scalar)
    {
        return LVector4
        (
            p_target.x * p_scalar,
            p_target.y * p_scalar,
            p_target.z * p_scalar,
            p_target.w * p_scalar
        );
    }

    LVector4 LVector4::Divide(const LVector4& p_left, float p_scalar)
    {
        LVector4 result(p_left);

        if (p_scalar == 0)
            throw std::logic_error("Division by 0");

        result.x /= p_scalar;
        result.y /= p_scalar;
        result.z /= p_scalar;
        result.w /= p_scalar;

        return result;
    }

    float LVector4::Length(const LVector4& p_target)
    {
        return sqrtf(p_target.x * p_target.x + p_target.y * p_target.y + p_target.z * p_target.z + p_target.w * p_target.w);
    }

    float LVector4::Dot(const LVector4& p_left, const LVector4& p_right)
    {
        return p_left.x * p_right.x + p_left.y * p_right.y + p_left.z * p_right.z + p_left.w * p_right.w;
    }

    LVector4 LVector4::Normalize(const LVector4& p_target)
    {
        float length = Length(p_target);

        if (length > 0.0f)
        {
            float targetLength = 1.0f / length;

            return LVector4
            (
                p_target.x * targetLength,
                p_target.y * targetLength,
                p_target.z * targetLength,
                p_target.w * targetLength
            );
        }
        else
        {
            return LVector4::Zero;
        }
    }

    LVector4 LVector4::Lerp(const LVector4& p_start, const LVector4& p_end, float p_alpha)
    {
        return (p_start + (p_end - p_start) * p_alpha);
    }

}
