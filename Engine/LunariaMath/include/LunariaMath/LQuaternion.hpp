/*
 * @copyright Copyright(c) 2024 Vladyslav Potapenko. All rights reserved.
 * @license Licensed under the MIT License. See LICENSE in the project root for license information.
 */

#pragma once

#include <string>

#include "LunariaMath/LVector3.hpp"
#include "LunariaMath/LMatrix3.hpp"
#include "LunariaMath/LMatrix4.hpp"

namespace Lunaria::Math {

    /*
    * Mathematical representation of a Quaternion with float precision
    */
    struct LQuaternion
    {
    public:
        float x;
        float y;
        float z;
        float w;

        /**
        * Return an identity quaternion
        */
        static const LQuaternion Identity;

        /**
        * Default Quaternion constructor (Create an identity quaternion with 1 as w)
        */
        LQuaternion();

        /**
        * Create an identity quaternion with a defined real value
        * @param p_real
        */
        LQuaternion(float p_real);

        /**
        * Create a quaternion from a set of 4 floats (x, y, z, w)
        * @param p_x Vector part of LQuaternion
        * @param p_y Vector part of LQuaternion
        * @param p_z Vector part of LQuaternion
        * @param p_w Real value of LQuaternion
        * @note In pure/applied Maths, we write W (or real), (Xi + Yj + Zk) (or Vector)
        */
        LQuaternion(float p_x, float p_y, float p_z, float p_w);

        /**
        * Copy Constructor
        * @param p_other
        */
        LQuaternion(const LQuaternion& p_other);

        /**
        * Construct from rotation matrix
        * @param p_rotationMatrix
        */
        LQuaternion(const LMatrix3& p_rotationMatrix);

        /**
        * Construct from rotation matrix
        * @param p_rotationMatrix
        */
        LQuaternion(const LMatrix4& p_rotationMatrix);

        /**
        * Construct from euler angles
        * @param p_euler
        */
        LQuaternion(const LVector3& p_euler);

        /**
        * Create a quaternion from a forward and up vector
        * @param p_forward
        * @param p_up
        */
        static LQuaternion LookAt(const LVector3& p_forward, const LVector3& p_up);

        /**
        * Check if the quaternion is Identity
        * if the quaternion has no rotation(meaning x,y,z axis values = 0), it's Identity
        * @param p_target
        */
        static bool IsIdentity(const LQuaternion& p_target);

        /*
        * Check if the quaternion is pure
        * if the quaternion has no real value(meaning real part = 0), it's pure
        * @param p_target
        */
        static bool IsPure(const LQuaternion& p_target);

        /**
        * Check if the quaternion is normalized
        * @param p_target
        */
        static bool IsNormalized(const LQuaternion& p_target);

        /**
        * Calculate the dot product between two quaternions
        * @param p_left
        * @param p_right
        */
        static float DotProduct(const LQuaternion& p_left, const LQuaternion& p_right);

        /**
        * Calculate the normalized of a quaternion
        * @param p_target
        */
        static LQuaternion Normalize(const LQuaternion& p_target);

        /**
        * Calculate the length of a quaternion
        * @param p_target
        */
        static float Length(const LQuaternion& p_target);

        /**
        * Calculate the length square of a quaternion
        * @param p_target
        */
        static float LengthSquare(const LQuaternion& p_target);

        /**
        * Return the angle of a quaternion
        * @param p_target
        */
        static float GetAngle(const LQuaternion& p_target);

        /**
        * Return the rotation axis of the given quaternion
        * @param p_target
        */
        static LVector3 GetRotationAxis(const LQuaternion& p_target);

        /**
        * Calculate the inverse of a quaternion
        * @param p_target
        */
        static LQuaternion Inverse(const LQuaternion& p_target);

        /**
        * Calculate the conjugate of a quaternion
        * @param p_target
        */
        static LQuaternion Conjugate(const LQuaternion& p_target);

        /**
        * Calculate the square of a quaternion
        * @param p_target
        */
        static LQuaternion Square(const LQuaternion& p_target);

        /**
        * Get the axis and the angle from a quaternion
        * @param p_target
        */
        static std::pair<LVector3, float> GetAxisAndAngle(const LQuaternion& p_target);

        /**
        * Calculate the angle between two quaternions.
        * @param p_left
        * @param p_right
        */
        static float AngularDistance(const LQuaternion& p_left, const LQuaternion& p_right);

        /**
        * Lerp two quaternions
        * @param p_start
        * @param p_end
        * @param p_alpha
        */
        static LQuaternion Lerp(const LQuaternion& p_start, const LQuaternion& p_end, float p_alpha);

        /**
        * Slerp two quaternions
        * @param p_start
        * @param p_end
        * @param p_alpha
        */
        static LQuaternion Slerp(const LQuaternion& p_start, const LQuaternion& p_end, float p_alpha);

        /**
        * NLerp two quaternions (= Lerp + normalization)
        * @param p_start
        * @param p_end
        * @param p_alpha
        */
        static LQuaternion NLerp(const LQuaternion& p_start, const LQuaternion& p_end, float p_alpha);

        /**
        * Rotate a point using a rotation quaternion (qpq^-1)
        * @param p_point
        * @param p_quaternion
        */
        static LVector3 RotatePoint(const LVector3& p_point, const LQuaternion& p_quaternion);

        /**
        * Rotate a point around a pivot point using a rotation quaternion
        * @param p_point
        * @param p_pivot
        * @param p_quaternion
        */
        static LVector3 RotatePoint(const LVector3& p_point, const LQuaternion& p_quaternion, const LVector3& p_pivot);

        /**
        * Returning Euler axis angles (In degrees) for each axis.
        * @param p_target
        */
        static LVector3 EulerAngles(const LQuaternion& p_target);

        /**
        * Return a rotation matrix (3x3) out of the given quaternion
        * @param p_target
        */
        static LMatrix3 ToMatrix3(const LQuaternion& p_target);

        /**
        * Return a rotation matrix (4x4) out of the given quaternion
        * @param p_target
        */
        static LMatrix4 ToMatrix4(const LQuaternion& p_target);

        bool operator==(const LQuaternion& p_otherQuat) const;
        bool operator!=(const LQuaternion& p_otherQuat) const;
        LQuaternion operator+(const LQuaternion& p_otherQuat) const;
        LQuaternion& operator+=(const LQuaternion& p_otherQuat);
        LQuaternion operator-(const LQuaternion& p_otherQuat) const;
        LQuaternion& operator-=(const LQuaternion& p_otherQuat);
        float operator|(const LQuaternion& p_otherQuat) const;
        LQuaternion& operator*=(const float p_scale);
        LQuaternion operator*(const float p_scale) const;
        LQuaternion operator*(const LQuaternion& p_otherQuat) const;
        LQuaternion& operator*=(const LQuaternion& p_otherQuat);
        LVector3 operator*(const LVector3& p_toMultiply) const;
        LMatrix3 operator*(const LMatrix3& p_multiply) const;
        LQuaternion& operator/=(const float p_scale);
        LQuaternion operator/(const float p_scale) const;
    };

}
