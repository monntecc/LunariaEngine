/*
 * @copyright Copyright(c) 2024 Vladyslav Potapenko. All rights reserved.
 * @license Licensed under the MIT License. See LICENSE in the project root for license information.
 */

#include <utility>
#include <stdexcept>

#include "LunariaMath/LVector2.hpp"

namespace Lunaria::Math {


    LVector2::LVector2(float p_x, float p_y) :
        x(p_x), y(p_y)
    {
    }

    LVector2::LVector2(const LVector2& p_toCopy) = default;

    LVector2 LVector2::operator-() const
    {
        return operator*(-1);
    }

    LVector2& LVector2::operator=(const LVector2& p_other) = default;

    LVector2 LVector2::operator+(const LVector2& p_other) const
    {
        return Add(*this, p_other);
    }

    LVector2& LVector2::operator+=(const LVector2& p_other)
    {
        *this = Add(*this, p_other);
        return *this;
    }

    LVector2 LVector2::operator-(const LVector2& p_other) const
    {
        return Substract(*this, p_other);
    }

    LVector2& LVector2::operator-=(const LVector2& p_other)
    {
        *this = Substract(*this, p_other);
        return *this;
    }

    LVector2 LVector2::operator*(float p_scalar) const
    {
        return Multiply(*this, p_scalar);
    }

    LVector2& LVector2::operator*=(float p_scalar)
    {
        *this = Multiply(*this, p_scalar);
        return *this;
    }

    LVector2 LVector2::operator/(float p_scalar) const
    {
        return Divide(*this, p_scalar);
    }

    LVector2& LVector2::operator/=(float p_scalar)
    {
        *this = Divide(*this, p_scalar);
        return *this;
    }

    bool LVector2::operator==(const LVector2& p_other) const
    {
        return
            this->x == p_other.x &&
            this->y == p_other.y;
    }

    bool LVector2::operator!=(const LVector2& p_other) const
    {
        return !operator==(p_other);
    }

    LVector2 LVector2::Add(const LVector2& p_left, const LVector2& p_right)
    {
        return LVector2
        (
            p_left.x + p_right.x,
            p_left.y + p_right.y
        );
    }

    LVector2 LVector2::Substract(const LVector2& p_left, const LVector2& p_right)
    {
        return LVector2
        (
            p_left.x - p_right.x,
            p_left.y - p_right.y
        );
    }

    LVector2 LVector2::Multiply(const LVector2& p_target, float p_scalar)
    {
        return LVector2
        (
            p_target.x * p_scalar,
            p_target.y * p_scalar
        );
    }

    LVector2 LVector2::Divide(const LVector2& p_left, float p_scalar)
    {
        LVector2 result(p_left);

        if (p_scalar == 0)
            throw std::logic_error("Division by 0");

        result.x /= p_scalar;
        result.y /= p_scalar;

        return result;
    }

    float LVector2::Length(const LVector2& p_target)
    {
        return sqrtf(p_target.x * p_target.x + p_target.y * p_target.y);
    }

    float LVector2::Dot(const LVector2& p_left, const LVector2& p_right)
    {
        return p_left.x * p_right.x + p_left.y * p_right.y;
    }

    LVector2 LVector2::Normalize(const LVector2& p_target)
    {
        float length = Length(p_target);

        if (length > 0.0f)
        {
            float targetLength = 1.0f / length;

            return LVector2
            (
                p_target.x * targetLength,
                p_target.y * targetLength
            );
        }
        else
        {
            return LVector2::Zero;
        }
    }

    LVector2 LVector2::Lerp(const LVector2& p_start, const LVector2& p_end, float p_alpha)
    {
        return (p_start + (p_end - p_start) * p_alpha);
    }

    float LVector2::AngleBetween(const LVector2& p_from, const LVector2& p_to)
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
