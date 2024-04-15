/*
 * @copyright Copyright(c) 2024 Vladyslav Potapenko. All rights reserved.
 * @license Licensed under the MIT License. See LICENSE in the project root for license information.
 */

#include <utility>
#include <stdexcept>
#include <cmath>

#include "LunariaMath/LVector3.hpp"

namespace Lunaria::Math {

    const LVector3 LVector3::One(1.0f, 1.0f, 1.0f);
    const LVector3 LVector3::Zero(0.0f, 0.0f, 0.0f);
    const LVector3 LVector3::Forward(0.0f, 0.0f, 1.0f);
    const LVector3 LVector3::Right(1.0f, 0.0f, 0.0f);
    const LVector3 LVector3::Up(0.0f, 1.0f, 0.0f);

    LVector3::LVector3(float p_x, float p_y, float p_z) : x(p_x), y(p_y), z(p_z)
    {
    }

    LVector3::LVector3(const LVector3& p_toCopy) = default;

    LVector3 LVector3::operator-() const
    {
        return operator*(-1);
    }

    LVector3& LVector3::operator=(const LVector3& p_other) = default;

    LVector3 LVector3::operator+(const LVector3& p_other) const
    {
        return Add(*this, p_other);
    }

    LVector3& LVector3::operator+=(const LVector3& p_other)
    {
        *this = Add(*this, p_other);
        return *this;
    }

    LVector3 LVector3::operator-(const LVector3& p_other) const
    {
        return Substract(*this, p_other);
    }

    LVector3& LVector3::operator-=(const LVector3& p_other)
    {
        *this = Substract(*this, p_other);
        return *this;
    }

    LVector3 LVector3::operator*(const LVector3& p_other) const
    {
        return Multiply(*this, p_other);
    }

    LVector3 LVector3::operator*(float p_scalar) const
    {
        return Multiply(*this, p_scalar);
    }

    LVector3& LVector3::operator*=(float p_scalar)
    {
        *this = Multiply(*this, p_scalar);
        return *this;
    }

    LVector3& LVector3::operator*=(const LVector3& p_other)
    {
        *this = Multiply(*this, p_other);
        return *this;
    }

    LVector3 LVector3::operator/(float p_scalar)
    {
        return Divide(*this, p_scalar);
    }

    LVector3& LVector3::operator/=(float p_scalar)
    {
        *this = Divide(*this, p_scalar);
        return *this;
    }

    bool LVector3::operator==(const LVector3& p_other)
    {
        return
            this->x == p_other.x &&
            this->y == p_other.y &&
            this->z == p_other.z;
    }

    bool LVector3::operator!=(const LVector3& p_other)
    {
        return !operator==(p_other);
    }

    LVector3 LVector3::Add(const LVector3& p_left, const LVector3& p_right)
    {
        return LVector3
        (
            p_left.x + p_right.x,
            p_left.y + p_right.y,
            p_left.z + p_right.z
        );
    }

    LVector3 LVector3::Substract(const LVector3& p_left, const LVector3& p_right)
    {
        return LVector3
        (
            p_left.x - p_right.x,
            p_left.y - p_right.y,
            p_left.z - p_right.z
        );
    }

    LVector3 LVector3::Multiply(const LVector3& p_target, float p_scalar)
    {
        return LVector3
        (
            p_target.x * p_scalar,
            p_target.y * p_scalar,
            p_target.z * p_scalar
        );
    }

    LVector3 LVector3::Multiply(const LVector3& p_left, const LVector3& p_right)
    {
        return LVector3
        (
            p_left.x * p_right.x,
            p_left.y * p_right.y,
            p_left.z * p_right.z
        );
    }

    LVector3 LVector3::Divide(const LVector3& p_left, float p_scalar)
    {
        LVector3 result(p_left);

        if (p_scalar == 0)
            throw std::logic_error("Division by 0");

        result.x /= p_scalar;
        result.y /= p_scalar;
        result.z /= p_scalar;

        return result;
    }

    float LVector3::Length(const LVector3& p_target)
    {
        return std::sqrt(p_target.x * p_target.x + p_target.y * p_target.y + p_target.z * p_target.z);
    }

    float LVector3::Dot(const LVector3& p_left, const LVector3& p_right)
    {
        return p_left.x * p_right.x + p_left.y * p_right.y + p_left.z * p_right.z;
    }

    float LVector3::Distance(const LVector3& p_left, const LVector3& p_right)
    {
        return std::sqrt
        (
            (p_left.x - p_right.x) * (p_left.x - p_right.x) +
            (p_left.y - p_right.y) * (p_left.y - p_right.y) +
            (p_left.z - p_right.z) * (p_left.z - p_right.z)
        );
    }

    LVector3 LVector3::Cross(const LVector3& p_left, const LVector3& p_right)
    {
        return LVector3
        (
            p_left.y * p_right.z - p_left.z * p_right.y,
            p_left.z * p_right.x - p_left.x * p_right.z,
            p_left.x * p_right.y - p_left.y * p_right.x
        );
    }

    LVector3 LVector3::Normalize(const LVector3& p_target)
    {
        float length = Length(p_target);

        if (length > 0.0f)
        {
            float targetLength = 1.0f / length;

            return LVector3
            (
                p_target.x * targetLength,
                p_target.y * targetLength,
                p_target.z * targetLength
            );
        }
        else
        {
            return LVector3::Zero;
        }
    }

    LVector3 LVector3::Lerp(const LVector3& p_start, const LVector3& p_end, float p_alpha)
    {
        return (p_start + (p_end - p_start) * p_alpha);
    }

    float LVector3::AngleBetween(const LVector3& p_from, const LVector3& p_to)
    {
        float lengthProduct = Length(p_from) * Length(p_to);

        if (lengthProduct > 0.0f)
        {
            float fractionResult = Dot(p_from, p_to) / lengthProduct;

            if (fractionResult >= -1.0f && fractionResult <= 1.0f)
                return acosf(fractionResult);
        }

        return 0.0f;
    }

}
