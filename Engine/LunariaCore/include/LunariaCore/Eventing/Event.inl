/*
 * @copyright Copyright(c) 2024 Vladyslav Potapenko. All rights reserved.
 * @license Licensed under the MIT License. See LICENSE in the project root for license information.
*/

#pragma once

#include "LunariaCore/Eventing/Event.hpp"

namespace Lunaria::Eventing {

    template<class... Args>
    ListenerID Event<Args...>::AddListener(Callback p_callback)
    {
        ListenerID listenerID = m_availableListenerID++;
        m_callbacks.emplace(listenerID, p_callback);
        return listenerID;
    }

    template<class... Args>
    ListenerID Event<Args...>::operator+=(Callback p_callback)
    {
        return AddListener(p_callback);
    }

    template<class... Args>
    bool Event<Args...>::RemoveListener(ListenerID p_listenerID)
    {
        return m_callbacks.erase(p_listenerID) != 0;
    }

    template<class... Args>
    bool Event<Args...>::operator-=(ListenerID p_listenerID)
    {
        return RemoveListener(p_listenerID);
    }

    template<class... Args>
    void Event<Args...>::RemoveAllListeners()
    {
        m_callbacks.clear();
    }

    template<class... Args>
    uint64_t Event<Args...>::GetListenerCount()
    {
        return m_callbacks.size();
    }

    template<class... Args>
    void Event<Args...>::Invoke(Args... p_args)
    {
        for (auto const& [key, value] : m_callbacks)
            value(p_args...);
    }

}
