/*
 * @copyright Copyright(c) 2024 Vladyslav Potapenko. All rights reserved.
 * @license Licensed under the MIT License. See LICENSE in the project root for license information.
 */

#pragma once

#include <cstdint>

#include "LunariaMath/LVector2.hpp"
#include "LunariaMath/LVector3.hpp"

namespace Lunaria::Math {

    /*
    * Mathematical representation of a 3x3 Matrix of floats
    */
    struct LMatrix3
    {
        float data[9];
        static const LMatrix3 Identity;

        /**
        * Default constructor
        */
        LMatrix3();

        /**
        * Set all elements to value
        * @param p_value
        */
        LMatrix3(float p_value);

        /**
        * Constructor
        * @param p_element1
        * @param p_element2
        * @param p_element3
        * @param p_element4
        * @param p_element5
        * @param p_element6
        * @param p_element7
        * @param p_element9
        * @param p_element8
        */
        LMatrix3(float p_element1, float p_element2, float p_element3,
            float p_element4, float p_element5, float p_element6,
            float p_element7, float p_element8, float p_element9);

        /**
        * Copy constructor
        * @param p_other
        */
        LMatrix3(const LMatrix3& p_other);

        /**
        * Copy assignment
        * @param p_other
        */
        LMatrix3& operator=(const LMatrix3& p_other);

        /**
        * Check if elements are equals
        * @param p_other
        */
        bool operator==(const LMatrix3& p_other);

        /**
        * Element-wise addition
        * @param p_other
        */
        LMatrix3 operator+(const LMatrix3& p_other);

        /**
        * Element-wise addition
        * @param p_other
        */
        LMatrix3& operator+=(const LMatrix3& p_other);

        /**
        * Element-wise subtraction
        * @param p_other
        */
        LMatrix3 operator-(const LMatrix3& p_other);

        /**
        * Element-wise subtraction
        * @param p_other
        */
        LMatrix3& operator-=(const LMatrix3& p_other);

        /**
        * Scalar Product
        * @param p_scalar
        */
        LMatrix3 operator*(float p_scalar) const;

        /**
        * Scalar Product
        * @param p_scalar
        */
        LMatrix3& operator*=(float p_scalar);

        /**
        * Vector Product
        * @param p_vector
        */
        LVector3 operator*(const LVector3& p_vector) const;

        /**
        * Matrix Product
        * @param p_other
        */
        LMatrix3 operator*(const LMatrix3& p_other) const;

        /**
        * Matrix Product
        * @param p_other
        */
        LMatrix3& operator*=(const LMatrix3& p_other);

        /**
        * Scalar Division
        * @param p_scalar
        */
        LMatrix3 operator/(float p_scalar);

        /**
        * Scalar Division
        * @param p_scalar
        */
        LMatrix3& operator/=(float p_scalar);

        /**
        * Matrix Division
        * @param p_other
        */
        LMatrix3 operator/(const LMatrix3& p_other);

        /**
        * Matrix Division
        * @param p_other
        */
        LMatrix3& operator/=(const LMatrix3& p_other);

        /**
        * Get element at index (row,column)
        * @param p_row
        * @param p_column
        */
        float& operator()(uint8_t p_row, uint8_t p_column);

        /**
        * Check if elements are equals
        * @param p_left
        * @param p_right
        */
        static bool AreEquals(const LMatrix3& p_left, const LMatrix3& p_right);

        /**
        * Element-wise addition
        * @param p_left
        * @param p_scalar
        */
        static LMatrix3 Add(const LMatrix3& p_left, float p_scalar);

        /**
        * Element-wise addition
        * @param p_left
        * @param p_right
        */
        static LMatrix3 Add(const LMatrix3& p_left, const LMatrix3& p_right);

        /**
        * Element-wise subtraction
        * @param p_left
        * @param p_scalar
        */
        static LMatrix3 Subtract(const LMatrix3& p_left, float p_scalar);

        /**
        * Element-wise subtractions
        * @param p_left
        * @param p_right
        */
        static LMatrix3 Subtract(const LMatrix3& p_left, const LMatrix3& p_right);

        /**
        * Scalar Product
        * @param p_left
        * @param p_scalar
        */
        static LMatrix3 Multiply(const LMatrix3& p_left, float p_scalar);

        /**
        * Vector Product
        * @param p_matrix
        * @param p_vector
        */
        static LVector3 Multiply(const LMatrix3& p_matrix, const LVector3& p_vector);

        /**
        * Matrix Product
        * @param p_left
        * @param p_right
        */
        static LMatrix3 Multiply(const LMatrix3& p_left, const LMatrix3& p_right);

        /**
        * Scalar Division
        * @param p_left
        * @param p_scalar
        */
        static LMatrix3 Divide(const LMatrix3& p_left, float p_scalar);

        /**
        * Matrix Division
        * @param p_left
        * @param p_right
        */
        static LMatrix3 Divide(const LMatrix3& p_left, const LMatrix3& p_right);

        /**
        * Compare to Identity matrix
        * @param p_matrix
        */
        static bool IsIdentity(const LMatrix3& p_matrix);

        /**
        * Compute matrix determinant
        * @param p_matrix
        */
        static float Determinant(const LMatrix3& p_matrix);

        /**
        * Return transposed matrix
        * @param p_matrix
        */
        static LMatrix3 Transpose(const LMatrix3& p_matrix);

        /**
        * Return Cofactor matrix
        * @param p_matrix
        */
        static LMatrix3 Cofactor(const LMatrix3& p_matrix);

        /**
        * Return Minor matrix
        * @param p_matrix
        */
        static LMatrix3 Minor(const LMatrix3& p_matrix);

        /**
        * Return AdJoint matrix
        * @param p_other
        */
        static LMatrix3 AdJoint(const LMatrix3& p_other);

        /**
        * Return inverse matrix
        * @param p_matrix
        */
        static LMatrix3 Inverse(const LMatrix3& p_matrix);

        /**
        * Return 2D translation matrix
        * @param p_translation
        */
        static LMatrix3 Translation(const LVector2& p_translation);

        /**
        * Translate matrix in 2D
        * @param p_matrix
        * @param p_translation
        */
        static LMatrix3 Translate(const LMatrix3& p_matrix, const LVector2& p_translation);

        /**
        * Return 2D rotation matrix
        * @param p_rotation angle in radians
        */
        static LMatrix3 Rotation(float p_rotation);

        /**
        * Rotate matrix in 2D
        * @param p_matrix
        * @param p_rotation angle in radians
        */
        static LMatrix3 Rotate(const LMatrix3& p_matrix, float p_rotation);

        /**
        * Return 2D scaling matrix
        * @param p_scale
        */
        static LMatrix3 Scaling(const LVector2& p_scale);

        /**
        * Scale matrix in 2D
        * @param p_matrix
        * @param p_scale
        */
        static LMatrix3 Scale(const LMatrix3& p_matrix, const LVector2& p_scale);

        /**
        * Get row
        * @param p_matrix
        * @param p_row
        */
        static LVector3 GetRow(const LMatrix3& p_matrix, uint8_t p_row);

        /**
        * Get Column
        * @param p_matrix
        * @param p_column
        */
        static LVector3 GetColumn(const LMatrix3& p_matrix, uint8_t p_column);
    };

}
