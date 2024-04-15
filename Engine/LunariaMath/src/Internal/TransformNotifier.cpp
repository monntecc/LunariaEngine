/*
 * @copyright Copyright(c) 2024 Vladyslav Potapenko. All rights reserved.
 * @license Licensed under the MIT License. See LICENSE in the project root for license information.
*/

#include "LunariaMath/Internal/TransformNotifier.hpp"

#include <ranges>

namespace Lunaria::Math::Internal {

    TransformNotifier::NotificationHandlerID TransformNotifier::AddNotificationHandler(NotificationHandler p_notificationHandler)
    {
        NotificationHandlerID handlerID = m_availableHandlerID++;
        m_notificationHandlers.emplace(handlerID, p_notificationHandler);
        return handlerID;
    }

    void TransformNotifier::NotifyChildren(ENotification p_notification)
    {
        if (!m_notificationHandlers.empty())
            for (const auto& handler : m_notificationHandlers | std::views::values)
                handler(p_notification);
    }

    bool TransformNotifier::RemoveNotificationHandler(const NotificationHandlerID& p_notificationHandlerID)
    {
        return m_notificationHandlers.erase(p_notificationHandlerID) != 0;
    }

}
