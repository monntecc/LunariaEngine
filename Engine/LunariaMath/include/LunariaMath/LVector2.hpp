/*
 * @copyright Copyright(c) 2024 Vladyslav Potapenko. All rights reserved.
 * @license Licensed under the MIT License. See LICENSE in the project root for license information.
 */

#pragma once

namespace Lunaria::Math {

    /*
     * Mathematical representation of a 2D vector of floats;
     */
    struct LVector2
    {
        static const LVector2 Zero;
        static const LVector2 One;

        float x, y;

        /*
         * Destructor
        */
        ~LVector2() = default;

        /*
         * Default constructor
         * @param p_x
         * @param p_y
        */
        LVector2(float p_x = 0.0f, float p_y = 0.0f);

        /*
         * Copy constructor
         * @param p_vector
        */
        LVector2(const LVector2& p_vector);

        /*
         * Move constructor
         * @param p_vector
        */
        LVector2(LVector2&& p_vector) noexcept = default;

        /*
         * Negation operator
        */
        LVector2 operator-() const;

        /**
        * Copy assignment
        * @param p_other
        */
        LVector2& operator=(const LVector2& p_other);

        /**
        * Calculate the sum of two vectors
        * @param p_other
        */
        LVector2 operator+(const LVector2& p_other) const;

        /**
        * Add the right vector to the left one
        * @param p_other
        */
        LVector2& operator+=(const LVector2& p_other);

        /**
        * Calculate the substraction of two vectors
        * @param p_other
        */
        LVector2 operator-(const LVector2& p_other) const;

        /**
        * Remove the right vector from the left one
        * @param p_other
        */
        LVector2& operator-=(const LVector2& p_other);

        /**
        * Calculate the multiplication of a vector with a scalar
        * @param p_scalar
        */
        LVector2 operator*(float p_scalar) const;

        /**
        * Multiply the vector by a scalar
        * @param p_scalar
        */
        LVector2& operator*=(float p_scalar);

        /**
        * Return the division of scalar and actual vector
        * @param p_scalar
        */
        LVector2 operator/(float p_scalar) const;

        /**
        * Divide scalar to the actual vector
        * @param p_scalar
        */
        LVector2& operator/=(float p_scalar);

        /**
        * Return true if the two vectors are equals
        * @param p_other
        */
        bool operator==(const LVector2& p_other) const;

        /**
        * Return true if the two vectors are different
        * @param p_other
        */
        bool operator!=(const LVector2& p_other) const;

        /**
        * Calculate the sum of two vectors
        * @param p_left (First vector)
        * @param p_right (Second vector)
        */
        static LVector2 Add(const LVector2& p_left, const LVector2& p_right);

        /**
        * Calculate the subs
        * traction of two vectors
        * @param p_left (First vector)
        * @param p_right (Second vector)
        */
        static LVector2 Substract(const LVector2& p_left, const LVector2& p_right);

        /**
        * Calculate the multiplication of a vector with a scalar
        * @param p_target
        * @param p_scalar
        */
        static LVector2 Multiply(const LVector2& p_target, float p_scalar);

        /**
        * Divide scalar to vector left
        * @param p_left
        * @param p_scalar
        */
        static LVector2 Divide(const LVector2& p_left, float p_scalar);

        /**
        * Return the length of a vector
        * @param p_target
        */
        static float Length(const LVector2& p_target);

        /**
        * Return the dot product of two vectors
        * @param p_left
        * @param p_right
        */
        static float Dot(const LVector2& p_left, const LVector2& p_right);

        /**
        * Return normalize of the given vector
        * @param p_target
        */
        static LVector2 Normalize(const LVector2& p_target);

        /**
        * Calculate the interpolation between two vectors
        * @param p_start
        * @param p_end
        * @param p_alpha
        */
        static LVector2 Lerp(const LVector2& p_start, const LVector2& p_end, float p_alpha);

        /**
        * Calculate the angle between two vectors
        * @param p_from
        * @param p_to
        */
        static float AngleBetween(const LVector2& p_from, const LVector2& p_to);
    };

}
