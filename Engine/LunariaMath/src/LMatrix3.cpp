/*
 * @copyright Copyright(c) 2024 Vladyslav Potapenko. All rights reserved.
 * @license Licensed under the MIT License. See LICENSE in the project root for license information.
*/

#include <string>
#include <stdexcept>
#include <cmath>

#include "LunariaMath/LMatrix3.hpp"

namespace Lunaria::Math {

    const LMatrix3 LMatrix3::Identity = LMatrix3(1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f);

    LMatrix3::LMatrix3()
    {
        memcpy(data, Identity.data, 9 * sizeof(float));
    }

    LMatrix3::LMatrix3(float p_value)
    {
        for (float& element : data)
            element = p_value;
    }

    LMatrix3::LMatrix3(float p_element1, float p_element2, float p_element3, float p_element4, float p_element5, float p_element6, float p_element7, float p_element8, float p_element9)
    {
        data[0] = p_element1;
        data[1] = p_element2;
        data[2] = p_element3;
        data[3] = p_element4;
        data[4] = p_element5;
        data[5] = p_element6;
        data[6] = p_element7;
        data[7] = p_element8;
        data[8] = p_element9;
    }

    LMatrix3::LMatrix3(const LMatrix3& p_other)
    {
        *this = p_other;
    }

    LMatrix3& LMatrix3::operator=(const LMatrix3& p_other)
    {
        memcpy(this->data, p_other.data, 9 * sizeof(float));
        return *this;
    }

    bool LMatrix3::operator==(const LMatrix3& p_other)
    {
        return AreEquals(*this, p_other);
    }

    LMatrix3 LMatrix3::operator+(const LMatrix3& p_other)
    {
        return Add(*this, p_other);
    }

    LMatrix3& LMatrix3::operator+=(const LMatrix3& p_other)
    {
        *this = Add(*this, p_other);
        return *this;
    }

    LMatrix3 LMatrix3::operator-(const LMatrix3& p_other)
    {
        return Subtract(*this, p_other);
    }

    LMatrix3& LMatrix3::operator-=(const LMatrix3& p_other)
    {
        *this = Subtract(*this, p_other);
        return *this;
    }

    LMatrix3 LMatrix3::operator*(float p_scalar) const
    {
        return Multiply(*this, p_scalar);
    }

    LMatrix3& LMatrix3::operator*=(float p_scalar)
    {
        *this = Multiply(*this, p_scalar);
        return *this;
    }

    LVector3 LMatrix3::operator*(const LVector3& p_vector) const
    {
        return Multiply(*this, p_vector);
    }

    LMatrix3 LMatrix3::operator*(const LMatrix3& p_other) const
    {
        return Multiply(*this, p_other);
    }

    LMatrix3& LMatrix3::operator*=(const LMatrix3& p_other)
    {
        *this = Multiply(*this, p_other);
        return *this;
    }

    LMatrix3 LMatrix3::operator/(float p_scalar)
    {
        return Divide(*this, p_scalar);
    }

    LMatrix3& LMatrix3::operator/=(float p_scalar)
    {
        *this = Divide(*this, p_scalar);
        return *this;
    }

    LMatrix3 LMatrix3::operator/(const LMatrix3& p_other)
    {
        return Divide(*this, p_other);
    }

    LMatrix3& LMatrix3::operator/=(const LMatrix3& p_other)
    {
        *this = Divide(*this, p_other);
        return *this;
    }

    float& LMatrix3::operator()(uint8_t p_row, uint8_t p_column)
    {
        if (p_row >= 3 || p_column >= 3)
            throw std::out_of_range(
                "Invalid index : " + std::to_string(p_row) + "," + std::to_string(p_column) + " is out of range");
        return data[3 * p_row + p_column];
    }

    bool LMatrix3::AreEquals(const LMatrix3& p_left, const LMatrix3& p_right)
    {
        return memcmp(&p_left, &p_right, 9 * sizeof(float)) == 0;
    }

    LMatrix3 LMatrix3::Add(const LMatrix3& p_left, float p_scalar)
    {
        LMatrix3 result(p_left);
        for (float& i : result.data)
            i += p_scalar;
        return result;
    }

    LMatrix3 LMatrix3::Add(const LMatrix3& p_left, const LMatrix3& p_right)
    {
        LMatrix3 result(p_left);
        for (uint8_t i = 0; i < 9; ++i)
            result.data[i] += p_right.data[i];
        return result;
    }

    LMatrix3 LMatrix3::Subtract(const LMatrix3& p_left, float p_scalar)
    {
        LMatrix3 result(p_left);
        for (float& element : result.data)
        {
            element -= p_scalar;
        }
        return result;
    }

    LMatrix3 LMatrix3::Subtract(const LMatrix3& p_left, const LMatrix3& p_right)
    {
        LMatrix3 result(p_left);
        for (uint8_t i = 0; i < 9; ++i)
            result.data[i] -= p_right.data[i];
        return result;
    }

    LMatrix3 LMatrix3::Multiply(const LMatrix3& p_left, float p_scalar)
    {
        LMatrix3 result(p_left);
        for (float& element : result.data)
        {
            element *= p_scalar;
        }
        return result;
    }

    LVector3 LMatrix3::Multiply(const LMatrix3& p_matrix, const LVector3& p_vector)
    {
        LVector3 result;
        result.x = ((p_matrix.data[0] * p_vector.x) + (p_matrix.data[1] * p_vector.y) + (p_matrix.data[2] *
            p_vector.z));
        result.y = ((p_matrix.data[3] * p_vector.x) + (p_matrix.data[4] * p_vector.y) + (p_matrix.data[5] *
            p_vector.z));
        result.z = ((p_matrix.data[6] * p_vector.x) + (p_matrix.data[7] * p_vector.y) + (p_matrix.data[8] *
            p_vector.z));

        return result;
    }

    LMatrix3 LMatrix3::Multiply(const LMatrix3& p_left, const LMatrix3& p_right)
    {
        return LMatrix3(
            (p_left.data[0] * p_right.data[0]) + (p_left.data[1] * p_right.data[3]) + (p_left.data[2
            ] * p_right.data[6]),
            (p_left.data[0] * p_right.data[1]) + (p_left.data[1] * p_right.data[4]) + (p_left.data[2
            ] * p_right.data[7]),
            (p_left.data[0] * p_right.data[2]) + (p_left.data[1] * p_right.data[5]) + (p_left.data[2
            ] * p_right.data[8]),

            (p_left.data[3] * p_right.data[0]) + (p_left.data[4] * p_right.data[3]) + (p_left.data[5
            ] * p_right.data[6]),
            (p_left.data[3] * p_right.data[1]) + (p_left.data[4] * p_right.data[4]) + (p_left.data[5
            ] * p_right.data[7]),
            (p_left.data[3] * p_right.data[2]) + (p_left.data[4] * p_right.data[5]) + (p_left.data[5
            ] * p_right.data[8]),

            (p_left.data[6] * p_right.data[0]) + (p_left.data[7] * p_right.data[3]) + (p_left.data[8
            ] * p_right.data[6]),
            (p_left.data[6] * p_right.data[1]) + (p_left.data[7] * p_right.data[4]) + (p_left.data[8
            ] * p_right.data[7]),
            (p_left.data[6] * p_right.data[2]) + (p_left.data[7] * p_right.data[5]) + (p_left.data[8
            ] * p_right.data[8]));
    }

    LMatrix3 LMatrix3::Divide(const LMatrix3& p_left, float p_scalar)
    {
        LMatrix3 result(p_left);
        for (float& element : result.data)
        {
            element /= p_scalar;
        }
        return result;
    }

    LMatrix3 LMatrix3::Divide(const LMatrix3& p_left, const LMatrix3& p_right)
    {
        return p_left * Inverse(p_right);
    }

    bool LMatrix3::IsIdentity(const LMatrix3& p_matrix)
    {
        return memcmp(Identity.data, p_matrix.data, 9 * sizeof(float)) == 0;
    }

    float LMatrix3::Determinant(const LMatrix3& p_matrix)
    {
        return p_matrix.data[0] * (p_matrix.data[4] * p_matrix.data[8] - p_matrix.data[5] * p_matrix.data[7])
            - p_matrix.data[3] * (p_matrix.data[1] * p_matrix.data[8] - p_matrix.data[2] * p_matrix.data[7])
            + p_matrix.data[6] * (p_matrix.data[1] * p_matrix.data[5] - p_matrix.data[2] * p_matrix.data[4]);
    }

    LMatrix3 LMatrix3::Transpose(const LMatrix3& p_matrix)
    {
        LMatrix3 result;

        result.data[0] = p_matrix.data[0];
        result.data[1] = p_matrix.data[3];
        result.data[2] = p_matrix.data[6];

        result.data[3] = p_matrix.data[1];
        result.data[4] = p_matrix.data[4];
        result.data[5] = p_matrix.data[7];

        result.data[6] = p_matrix.data[2];
        result.data[7] = p_matrix.data[5];
        result.data[8] = p_matrix.data[8];

        return result;
    }

    LMatrix3 LMatrix3::Cofactor(const LMatrix3& p_matrix)
    {
        return LMatrix3(
            ((p_matrix.data[4] * p_matrix.data[8]) - (p_matrix.data[5] * p_matrix.data[7])), //0
            -((p_matrix.data[3] * p_matrix.data[8]) - (p_matrix.data[5] * p_matrix.data[6])), //1
            ((p_matrix.data[3] * p_matrix.data[7]) - (p_matrix.data[4] * p_matrix.data[6])), //2
            -((p_matrix.data[1] * p_matrix.data[8]) - (p_matrix.data[2] * p_matrix.data[7])), //3
            ((p_matrix.data[0] * p_matrix.data[8]) - (p_matrix.data[2] * p_matrix.data[6])), //4
            -((p_matrix.data[0] * p_matrix.data[7]) - (p_matrix.data[1] * p_matrix.data[6])), //5
            ((p_matrix.data[1] * p_matrix.data[5]) - (p_matrix.data[2] * p_matrix.data[4])), //6
            -((p_matrix.data[0] * p_matrix.data[5]) - (p_matrix.data[2] * p_matrix.data[3])), //7 
            ((p_matrix.data[0] * p_matrix.data[4]) - (p_matrix.data[1] * p_matrix.data[3]))); //8
    }

    LMatrix3 LMatrix3::Minor(const LMatrix3& p_matrix)
    {
        return LMatrix3(
            ((p_matrix.data[4] * p_matrix.data[8]) - (p_matrix.data[5] * p_matrix.data[7])), //0
            ((p_matrix.data[3] * p_matrix.data[8]) - (p_matrix.data[5] * p_matrix.data[6])), //1
            ((p_matrix.data[3] * p_matrix.data[7]) - (p_matrix.data[4] * p_matrix.data[6])), //2
            ((p_matrix.data[1] * p_matrix.data[8]) - (p_matrix.data[2] * p_matrix.data[7])), //3
            ((p_matrix.data[0] * p_matrix.data[8]) - (p_matrix.data[2] * p_matrix.data[6])), //4
            ((p_matrix.data[0] * p_matrix.data[7]) - (p_matrix.data[1] * p_matrix.data[6])), //5
            ((p_matrix.data[1] * p_matrix.data[5]) - (p_matrix.data[2] * p_matrix.data[4])), //6
            ((p_matrix.data[0] * p_matrix.data[5]) - (p_matrix.data[2] * p_matrix.data[3])), //7 
            ((p_matrix.data[0] * p_matrix.data[4]) - (p_matrix.data[1] * p_matrix.data[3]))); //8
    }

    LMatrix3 LMatrix3::AdJoint(const LMatrix3& p_other)
    {
        return Transpose(Cofactor(p_other));
    }

    LMatrix3 LMatrix3::Inverse(const LMatrix3& p_matrix)
    {
        const float determinant = Determinant(p_matrix);
        if (determinant == 0)
            throw std::logic_error("Division by 0");

        return AdJoint(p_matrix) / determinant;
    }

    LMatrix3 LMatrix3::Translation(const LVector2& p_translation)
    {
        return {
            1, 0, p_translation.x,
            0, 1, p_translation.y,
            0, 0, 1
        };
    }

    LMatrix3 LMatrix3::Translate(const LMatrix3& p_matrix, const LVector2& p_translation)
    {
        return p_matrix * Translation(p_translation);
    }

    LMatrix3 LMatrix3::Rotation(float p_rotation)
    {
        return LMatrix3(std::cos(p_rotation), -std::sin(p_rotation), 0,
            std::sin(p_rotation), std::cos(p_rotation), 0,
            0, 0, 1);
    }

    LMatrix3 LMatrix3::Rotate(const LMatrix3& p_matrix, float p_rotation)
    {
        return p_matrix * Rotation(p_rotation);
    }

    LMatrix3 LMatrix3::Scaling(const LVector2& p_scale)
    {
        return LMatrix3(p_scale.x, 0, 0,
            0, p_scale.y, 0,
            0, 0, 1);
    }

    LMatrix3 LMatrix3::Scale(const LMatrix3& p_matrix, const LVector2& p_scale)
    {
        return p_matrix * Scaling(p_scale);
    }

    LVector3 LMatrix3::GetRow(const LMatrix3& p_matrix, uint8_t p_row)
    {
        if (p_row >= 3)
            throw std::out_of_range("Invalid index : " + std::to_string(p_row) + " is out of range");

        return LVector3(p_matrix.data[p_row * 3], p_matrix.data[p_row * 3 + 1], p_matrix.data[p_row * 3 + 2]);
    }

    LVector3 LMatrix3::GetColumn(const LMatrix3& p_matrix, uint8_t p_column)
    {
        if (p_column >= 3)
            throw std::out_of_range("Invalid index : " + std::to_string(p_column) + " is out of range");

        return LVector3(p_matrix.data[p_column + 6], p_matrix.data[p_column + 3], p_matrix.data[p_column]);
    }

}
