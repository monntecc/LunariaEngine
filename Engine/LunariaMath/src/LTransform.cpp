/*
 * @copyright Copyright(c) 2024 Vladyslav Potapenko. All rights reserved.
 * @license Licensed under the MIT License. See LICENSE in the project root for license information.
*/

#include "LunariaMath/LTransform.hpp"

namespace Lunaria::Math {

    FTransform::FTransform(LVector3 p_localPosition, LQuaternion p_localRotation, LVector3 p_localScale) :
        m_notificationHandlerID(-1),
        m_parent(nullptr)
    {
        GenerateMatricesLocal(p_localPosition, p_localRotation, p_localScale);
    }

    FTransform::~FTransform()
    {
        Notifier.NotifyChildren(Internal::TransformNotifier::ENotification::TRANSFORM_DESTROYED);
    }

    void FTransform::NotificationHandler(Internal::TransformNotifier::ENotification p_notification)
    {
        switch (p_notification)
        {
        case Internal::TransformNotifier::ENotification::TRANSFORM_CHANGED:
            UpdateWorldMatrix();
            break;

        case Internal::TransformNotifier::ENotification::TRANSFORM_DESTROYED:
            /*
            * RemoveParent() is not called here because it is unsafe to remove a notification handler
            * while the parent is iterating on his notification handlers (Segfault otherwise)
            */
            GenerateMatricesLocal(m_worldPosition, m_worldRotation, m_worldScale);
            m_parent = nullptr;
            UpdateWorldMatrix();
            break;
        }
    }

    void FTransform::SetParent(FTransform& p_parent)
    {
        m_parent = &p_parent;

        m_notificationHandlerID = m_parent->Notifier.AddNotificationHandler(std::bind(&FTransform::NotificationHandler, this, std::placeholders::_1));

        UpdateWorldMatrix();
    }

    bool FTransform::RemoveParent()
    {
        if (m_parent != nullptr)
        {
            m_parent->Notifier.RemoveNotificationHandler(m_notificationHandlerID);
            m_parent = nullptr;
            UpdateWorldMatrix();

            return true;
        }

        return false;
    }

    bool FTransform::HasParent() const
    {
        return m_parent != nullptr;
    }

    void FTransform::GenerateMatricesLocal(LVector3 p_position, LQuaternion p_rotation, LVector3 p_scale)
    {
        m_localMatrix = LMatrix4::Translation(p_position) * LQuaternion::ToMatrix4(LQuaternion::Normalize(p_rotation)) * LMatrix4::Scaling(p_scale);
        m_localPosition = p_position;
        m_localRotation = p_rotation;
        m_localScale = p_scale;

        UpdateWorldMatrix();
    }

    void FTransform::GenerateMatricesWorld(LVector3 p_position, LQuaternion p_rotation, LVector3 p_scale)
    {
        m_worldMatrix = LMatrix4::Translation(p_position) * LQuaternion::ToMatrix4(LQuaternion::Normalize(p_rotation)) * LMatrix4::Scaling(p_scale);
        m_worldPosition = p_position;
        m_worldRotation = p_rotation;
        m_worldScale = p_scale;

        UpdateLocalMatrix();
    }

    void FTransform::UpdateWorldMatrix()
    {
        m_worldMatrix = HasParent() ? m_parent->m_worldMatrix * m_localMatrix : m_localMatrix;
        PreDecomposeWorldMatrix();

        Notifier.NotifyChildren(Internal::TransformNotifier::ENotification::TRANSFORM_CHANGED);
    }

    void FTransform::UpdateLocalMatrix()
    {
        m_localMatrix = HasParent() ? LMatrix4::Inverse(m_parent->m_worldMatrix) * m_worldMatrix : m_worldMatrix;
        PreDecomposeLocalMatrix();

        Notifier.NotifyChildren(Internal::TransformNotifier::ENotification::TRANSFORM_CHANGED);
    }

    void FTransform::SetLocalPosition(LVector3 p_newPosition)
    {
        GenerateMatricesLocal(p_newPosition, m_localRotation, m_localScale);
    }

    void FTransform::SetLocalRotation(LQuaternion p_newRotation)
    {
        GenerateMatricesLocal(m_localPosition, p_newRotation, m_localScale);
    }

    void FTransform::SetLocalScale(LVector3 p_newScale)
    {
        GenerateMatricesLocal(m_localPosition, m_localRotation, p_newScale);
    }

    void FTransform::SetWorldPosition(LVector3 p_newPosition)
    {
        GenerateMatricesWorld(p_newPosition, m_worldRotation, m_worldScale);
    }

    void FTransform::SetWorldRotation(LQuaternion p_newRotation)
    {
        GenerateMatricesWorld(m_worldPosition, p_newRotation, m_worldScale);
    }

    void FTransform::SetWorldScale(LVector3 p_newScale)
    {
        GenerateMatricesWorld(m_worldPosition, m_worldRotation, p_newScale);
    }

    void FTransform::TranslateLocal(const LVector3& p_translation)
    {
        SetLocalPosition(m_localPosition + p_translation);
    }

    void FTransform::RotateLocal(const LQuaternion& p_rotation)
    {
        SetLocalRotation(m_localRotation * p_rotation);
    }

    void FTransform::ScaleLocal(const LVector3& p_scale)
    {
        SetLocalScale(LVector3
        (
            m_localScale.x * p_scale.x,
            m_localScale.y * p_scale.y,
            m_localScale.z * p_scale.z
        ));
    }

    const LVector3& FTransform::GetLocalPosition() const
    {
        return m_localPosition;
    }

    const LQuaternion& FTransform::GetLocalRotation() const
    {
        return m_localRotation;
    }

    const LVector3& FTransform::GetLocalScale() const
    {
        return m_localScale;
    }

    const LVector3& FTransform::GetWorldPosition() const
    {
        return m_worldPosition;
    }

    const LQuaternion& FTransform::GetWorldRotation() const
    {
        return m_worldRotation;
    }

    const LVector3& FTransform::GetWorldScale() const
    {
        return m_worldScale;
    }

    const LMatrix4& FTransform::GetLocalMatrix() const
    {
        return m_localMatrix;
    }

    const LMatrix4& FTransform::GetWorldMatrix() const
    {
        return m_worldMatrix;
    }

    LVector3 FTransform::GetWorldForward() const
    {
        return m_worldRotation * LVector3::Forward;
    }

    LVector3 FTransform::GetWorldUp() const
    {
        return m_worldRotation * LVector3::Up;
    }

    LVector3 FTransform::GetWorldRight() const
    {
        return m_worldRotation * LVector3::Right;
    }

    LVector3 FTransform::GetLocalForward() const
    {
        return m_localRotation * LVector3::Forward;
    }

    LVector3 FTransform::GetLocalUp() const
    {
        return m_localRotation * LVector3::Up;
    }

    LVector3 FTransform::GetLocalRight() const
    {
        return m_localRotation * LVector3::Right;
    }

    void FTransform::PreDecomposeWorldMatrix()
    {
        m_worldPosition.x = m_worldMatrix(0, 3);
        m_worldPosition.y = m_worldMatrix(1, 3);
        m_worldPosition.z = m_worldMatrix(2, 3);

        LVector3 columns[3] =
        {
            { m_worldMatrix(0, 0), m_worldMatrix(1, 0), m_worldMatrix(2, 0)},
            { m_worldMatrix(0, 1), m_worldMatrix(1, 1), m_worldMatrix(2, 1)},
            { m_worldMatrix(0, 2), m_worldMatrix(1, 2), m_worldMatrix(2, 2)},
        };

        m_worldScale.x = LVector3::Length(columns[0]);
        m_worldScale.y = LVector3::Length(columns[1]);
        m_worldScale.z = LVector3::Length(columns[2]);

        if (m_worldScale.x)
        {
            columns[0] /= m_worldScale.x;
        }
        if (m_worldScale.y)
        {
            columns[1] /= m_worldScale.y;
        }
        if (m_worldScale.z)
        {
            columns[2] /= m_worldScale.z;
        }

        LMatrix3 rotationMatrix
        (
            columns[0].x, columns[1].x, columns[2].x,
            columns[0].y, columns[1].y, columns[2].y,
            columns[0].z, columns[1].z, columns[2].z
        );

        m_worldRotation = LQuaternion(rotationMatrix);
    }

    void FTransform::PreDecomposeLocalMatrix()
    {
        m_localPosition.x = m_localMatrix(0, 3);
        m_localPosition.y = m_localMatrix(1, 3);
        m_localPosition.z = m_localMatrix(2, 3);

        LVector3 columns[3] =
        {
            { m_localMatrix(0, 0), m_localMatrix(1, 0), m_localMatrix(2, 0)},
            { m_localMatrix(0, 1), m_localMatrix(1, 1), m_localMatrix(2, 1)},
            { m_localMatrix(0, 2), m_localMatrix(1, 2), m_localMatrix(2, 2)},
        };

        m_localScale.x = LVector3::Length(columns[0]);
        m_localScale.y = LVector3::Length(columns[1]);
        m_localScale.z = LVector3::Length(columns[2]);

        if (m_localScale.x)
        {
            columns[0] /= m_localScale.x;
        }
        if (m_localScale.y)
        {
            columns[1] /= m_localScale.y;
        }
        if (m_localScale.z)
        {
            columns[2] /= m_localScale.z;
        }

        LMatrix3 rotationMatrix
        (
            columns[0].x, columns[1].x, columns[2].x,
            columns[0].y, columns[1].y, columns[2].y,
            columns[0].z, columns[1].z, columns[2].z
        );

        m_localRotation = LQuaternion(rotationMatrix);
    }

}
