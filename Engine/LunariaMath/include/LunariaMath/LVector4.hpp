/*
 * @copyright Copyright(c) 2024 Vladyslav Potapenko. All rights reserved.
 * @license Licensed under the MIT License. See LICENSE in the project root for license information.
 */

#pragma once

#include "LunariaMath/LVector3.hpp"

namespace Lunaria::Math {

    /**
	* Mathematic representation of a 4D vector of floats
	*/
	struct LVector4
	{
		static const LVector4 One;
		static const LVector4 Zero;

		float x;
		float y;
		float z;
		float w;

		/**
		* Default constructor
		* @param p_x
		* @param p_y
		* @param p_z
		* @param p_w
		*/
		LVector4(float p_x = 0.0f, float p_y = 0.0f, float p_z = 0.0f, float p_w = 0.0f);

		/**
		* Default constructor
		* @param p_vector
		* @param p_w
		*/
        LVector4(const LVector4& p_vector, float p_w = 0.0f);

		/**
		* Move constructor
		* @param p_toMove
		*/
		LVector4(LVector4&& p_toMove) noexcept = default;

		/**
		* Negation
		*/
		LVector4 operator-() const;

		/**
		* Copy assignment
		* @param p_other
		*/
		LVector4& operator=(const LVector4& p_other);

		/**
		* Calculate the sum of two vectors
		* @param p_other
		*/
		LVector4 operator+(const LVector4& p_other) const;

		/**
		* Add the right vector to the left one
		* @param p_other
		*/
		LVector4& operator+=(const LVector4& p_other);

		/**
		* Calculate the substraction of two vectors
		* @param p_other
		*/
		LVector4 operator-(const LVector4& p_other) const;

		/**
		* Remove the right vector from the left one
		* @param p_other
		*/
		LVector4& operator-=(const LVector4& p_other);

		/**
		* Calculate the multiplication of a vector with a scalar
		* @param p_scalar
		*/
		LVector4 operator*(float p_scalar) const;

		/**
		* Multiply the vector by a scalar
		* @param p_scalar
		*/
		LVector4& operator*=(float p_scalar);

		/**
		* Return the division of scalar and actual vector
		* @param p_scalar
		*/
		LVector4 operator/(float p_scalar) const;

		/**
		* Divide scalar to the actual vector
		* @param p_scalar
		*/
		LVector4& operator/=(float p_scalar);

		/**
		* Return true if the two vectors are equals
		* @param p_other
		*/
		bool operator==(const LVector4& p_other) const;

		/**
		* Return true if the two vectors are different
		* @param p_other
		*/
		bool operator!=(const LVector4& p_other) const;

		/**
		* Calculate the sum of two vectors
		* @param p_left (First vector)
		* @param p_right (Second vector)
		*/
		static LVector4 Add(const LVector4& p_left, const LVector4& p_right);

		/**
		* Calculate the substraction of two vectors
		* @param p_left (First vector)
		* @param p_right (Second vector)
		*/
		static LVector4 Substract(const LVector4& p_left, const LVector4& p_right);

		/**
		* Calculate the multiplication of a vector with a scalar
		* @param p_target
		* @param p_scalar
		*/
		static LVector4 Multiply(const LVector4& p_target, float p_scalar);

		/**
		* Divide scalar to vector left
		* @param p_left
		* @param p_scalar
		*/
		static LVector4 Divide(const LVector4& p_left, float p_scalar);

		/**
		* Return the length of a vector
		* @param p_target
		*/
		static float Length(const LVector4& p_target);

		/**
		* Return the dot product of two vectors
		* @param p_left
		* @param p_right
		*/
		static float Dot(const LVector4& p_left, const LVector4& p_right);

		/**
		* Return normalize of the given vector
		* @param p_target
		*/
		static LVector4 Normalize(const LVector4& p_target);

		/**
		* Calculate the interpolation between two vectors
		* @param p_start
		* @param p_end
		* @param p_alpha
		*/
		static LVector4 Lerp(const LVector4& p_start, const LVector4& p_end, float p_alpha);
	};

}
