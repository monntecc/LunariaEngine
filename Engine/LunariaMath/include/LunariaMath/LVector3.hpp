/*
 * @copyright Copyright(c) 2024 Vladyslav Potapenko. All rights reserved.
 * @license Licensed under the MIT License. See LICENSE in the project root for license information.
 */

#pragma once

namespace Lunaria::Math {

    /**
    * Mathematical representation of a 3D vector of floats
    */
    struct LVector3
    {
        static const LVector3 One;
        static const LVector3 Zero;
        static const LVector3 Forward;
        static const LVector3 Right;
        static const LVector3 Up;

        float x;
        float y;
        float z;

        /**
        * Default constructor
        * @param p_x
        * @param p_y
        * @param p_z
        */
        LVector3(float p_x = 0.0f, float p_y = 0.0f, float p_z = 0.0f);

        /**
        * Copy constructor
        * @param p_toCopy
        */
        LVector3(const LVector3& p_toCopy);

        /**
        * Move constructor
        * @param p_toMove
        */
        LVector3(LVector3&& p_toMove) noexcept = default;

        /**
        * Negation
        */
        LVector3 operator-() const;

        /**
        * Copy assignment
        * @param p_other
        */
        LVector3& operator=(const LVector3& p_other);

        /**
        * Calculate the sum of two vectors
        * @param p_other
        */
        LVector3 operator+(const LVector3& p_other) const;

        /**
        * Add the right vector to the left one
        * @param p_other
        */
        LVector3& operator+=(const LVector3& p_other);

        /**
        * Calculate the substraction of two vectors
        * @param p_other
        */
        LVector3 operator-(const LVector3& p_other) const;

        /**
        * Remove the right vector from the left one
        * @param p_other
        */
        LVector3& operator-=(const LVector3& p_other);

        /**
        * Multiple two vector together component-wise
        * @param p_other
        */
        LVector3 operator*(const LVector3& p_other) const;

        /**
        * Calculate the multiplication of a vector with a scalar
        * @param p_scalar
        */
        LVector3 operator*(float p_scalar) const;

        /**
        * Multiply the vector by a scalar
        * @param p_scalar
        */
        LVector3& operator*=(float p_scalar);

        /**
        * Multiple two vector together component-wise
        * @param p_other
        */
        LVector3& operator*=(const LVector3& p_other);

        /**
        * Return the division of scalar and actual vector
        * @param p_scalar
        */
        LVector3 operator/(float p_scalar);

        /**
        * Divide scalar to the actual vector
        * @param p_scalar
        */
        LVector3& operator/=(float p_scalar);

        /**
        * Return true if the two vectors are equals
        * @param p_other
        */
        bool operator==(const LVector3& p_other);

        /**
        * Return true if the two vectors are different
        * @param p_other
        */
        bool operator!=(const LVector3& p_other);

        /**
        * Calculate the sum of two vectors
        * @param p_left (First vector)
        * @param p_right (Second vector)
        */
        static LVector3 Add(const LVector3& p_left, const LVector3& p_right);

        /**
        * Calculate the substraction of two vectors
        * @param p_left (First vector)
        * @param p_right (Second vector)
        */
        static LVector3 Substract(const LVector3& p_left, const LVector3& p_right);

        /**
        * Calculate the multiplication of a vector with a scalar
        * @param p_target
        * @param p_scalar
        */
        static LVector3 Multiply(const LVector3& p_target, float p_scalar);

        /**
        * Multiple two vectors component-wise
        * @param p_left
        * @param p_right
        */
        static LVector3 Multiply(const LVector3& p_left, const LVector3& p_right);

        /**
        * Divide scalar to vector left
        * @param p_left
        * @param p_scalar
        */
        static LVector3 Divide(const LVector3& p_left, float p_scalar);

        /**
        * Return the length of a vector
        * @param p_target
        */
        static float Length(const LVector3& p_target);

        /**
        * Return the dot product of two vectors
        * @param p_left
        * @param p_right
        */
        static float Dot(const LVector3& p_left, const LVector3& p_right);

        /**
        * Return the distance between two vectors
        * @param p_left
        * @param p_right
        */
        static float Distance(const LVector3& p_left, const LVector3& p_right);

        /**
        * Return the cross product of two vectors
        * @param p_left
        * @param p_right
        */
        static LVector3 Cross(const LVector3& p_left, const LVector3& p_right);

        /**
        * Return the normalize of the given vector
        * @param p_target
        */
        static LVector3 Normalize(const LVector3& p_target);

        /**
        * Calculate the interpolation between two vectors
        * @param p_start
        * @param p_end
        * @param p_alpha
        */
        static LVector3 Lerp(const LVector3& p_start, const LVector3& p_end, float p_alpha);

        /**
        * Calculate the angle between two vectors
        * @param p_from
        * @param p_to
        */
        static float AngleBetween(const LVector3& p_from, const LVector3& p_to);
    };

}
