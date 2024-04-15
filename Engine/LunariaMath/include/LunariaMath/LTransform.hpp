/*
 * @copyright Copyright(c) 2024 Vladyslav Potapenko. All rights reserved.
 * @license Licensed under the MIT License. See LICENSE in the project root for license information.
 */

#pragma once

#include "LunariaMath/Internal/TransformNotifier.hpp"
#include "LunariaMath/LQuaternion.hpp"
#include "LunariaMath/LMatrix4.hpp"
#include "LunariaMath/LVector3.hpp"

namespace Lunaria::Math {

    /**
    * Mathematical representation of a 3D transformation with float precision
    */
    class FTransform
    {
    public:
        /**
        * Create a transform without setting a parent
        * @param p_localPosition
        * @param p_localRotation
        * @param p_localScale
        */
        explicit FTransform(LVector3 p_localPosition = LVector3(0.0f, 0.0f, 0.0f), LQuaternion p_localRotation = LQuaternion::Identity, LVector3 p_localScale = LVector3(1.0f, 1.0f, 1.0f));

        /**
        * Destructor of the transform.
        * Will notify children on destruction
        */
        ~FTransform();

        /**
        * Simple callback that will treat parent notifications
        * @param p_notification
        */
        void NotificationHandler(Internal::TransformNotifier::ENotification p_notification);

        /**
        * Defines a parent to the transform
        * @param p_parent
        */
        void SetParent(FTransform& p_parent);

        /**
        * Set the parent to nullptr and recalculate world matrix
        * Returns true on success
        */
        bool RemoveParent();

        /**
        * Check if the transform has a parent
        */
        [[nodiscard]] bool HasParent() const;

        /**
        * Initialize transform with raw data from world info
        * @param p_position
        * @param p_rotation
        * @param p_scale
        */
        void GenerateMatricesWorld(LVector3 p_position, LQuaternion p_rotation, LVector3 p_scale);

        /**
        * Initialize transform with raw data from local info
        * @param p_position
        * @param p_rotation
        * @param p_scale
        */
        void GenerateMatricesLocal(LVector3 p_position, LQuaternion p_rotation, LVector3 p_scale);

        /**
        * Re-update world matrix to use parent transformations
        */
        void UpdateWorldMatrix();

        /**
        * Re-update local matrix to use parent transformations
        */
        void UpdateLocalMatrix();

        /**
        * Set the position of the transform in the local space
        * @param p_newPosition
        */
        void SetLocalPosition(LVector3 p_newPosition);

        /**
        * Set the rotation of the transform in the local space
        * @param p_newRotation
        */
        void SetLocalRotation(LQuaternion p_newRotation);

        /**
        * Set the scale of the transform in the local space
        * @param p_newScale
        */
        void SetLocalScale(LVector3 p_newScale);

        /**
        * Set the position of the transform in world space
        * @param p_newPosition
        */
        void SetWorldPosition(LVector3 p_newPosition);

        /**
        * Set the rotation of the transform in world space
        * @param p_newRotation
        */
        void SetWorldRotation(LQuaternion p_newRotation);

        /**
        * Set the scale of the transform in world space
        * @param p_newScale
        */
        void SetWorldScale(LVector3 p_newScale);

        /**
        * Translate in the local space
        * @param p_translation
        */
        void TranslateLocal(const LVector3& p_translation);

        /**
        * Rotate in the local space
        * @param p_rotation
        */
        void RotateLocal(const LQuaternion& p_rotation);

        /**
        * Scale in the local space
        * @param p_scale
        */
        void ScaleLocal(const LVector3& p_scale);

        /**
        * Return the position in local space
        */
        [[nodiscard]] const LVector3& GetLocalPosition() const;

        /**
        * Return the rotation in local space
        */
        [[nodiscard]] const LQuaternion& GetLocalRotation() const;

        /**
        * Return the scale in local space
        */
        [[nodiscard]] const LVector3& GetLocalScale() const;

        /**
        * Return the position in world space
        */
        [[nodiscard]] const LVector3& GetWorldPosition() const;

        /**
        * Return the rotation in world space
        */
        [[nodiscard]] const LQuaternion& GetWorldRotation() const;

        /**
        * Return the scale in world space
        */
        [[nodiscard]] const LVector3& GetWorldScale() const;

        /**
        * Return the local matrix
        */
        [[nodiscard]] const LMatrix4& GetLocalMatrix() const;

        /**
        * Return the world matrix
        */
        [[nodiscard]] const LMatrix4& GetWorldMatrix() const;

        /**
        * Return the transform world forward
        */
        [[nodiscard]] LVector3 GetWorldForward() const;

        /**
        * Return the transform world up
        */
        [[nodiscard]] LVector3 GetWorldUp() const;

        /**
        * Return the transform world right
        */
        [[nodiscard]] LVector3 GetWorldRight() const;

        /**
        * Return the transform local forward
        */
        [[nodiscard]] LVector3 GetLocalForward() const;

        /**
        * Return the transform local up
        */
        [[nodiscard]] LVector3 GetLocalUp() const;

        /**
        * Return the transform local right
        */
        [[nodiscard]] LVector3 GetLocalRight() const;

    public:
        Internal::TransformNotifier Notifier;
        Internal::TransformNotifier::NotificationHandlerID m_notificationHandlerID;

    private:
        void PreDecomposeWorldMatrix();
        void PreDecomposeLocalMatrix();

        /* Pre-decomposed data to prevent multiple decomposition */
        LVector3 m_localPosition;
        LQuaternion m_localRotation;
        LVector3 m_localScale;
        LVector3 m_worldPosition;
        LQuaternion m_worldRotation;
        LVector3 m_worldScale;

        LMatrix4 m_localMatrix;
        LMatrix4 m_worldMatrix;

        FTransform* m_parent;
    };

}
