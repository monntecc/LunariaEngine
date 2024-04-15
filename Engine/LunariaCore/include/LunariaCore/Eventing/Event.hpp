/*
 * @copyright Copyright(c) 2024 Vladyslav Potapenko. All rights reserved.
 * @license Licensed under the MIT License. See LICENSE in the project root for license information.
*/

#pragma once

#include "LunariaCore/Global/Base.hpp"

namespace Lunaria::Eventing {

    /*
    * The ID of the listener (Registered callback)
    * This value is needed to remove a listener from the event system
    */
    using ListenerID = uint64_t;

    /*
    * A simple event that contains a set of listeners. These functions will be called on invoke
    */
    template<class... Args>
    class LUNARIA_API Event
    {
    public:
        /*
        * Simple shortcut for a generic function without return value
        */
        using Callback = std::function<void(Args...)>;

        /**
        * Add a function callback to this event
        * Also return the ID of the new listener (You should store the returned ID if you want to remove the listener later)
        * @param p_callback
        */
        ListenerID AddListener(Callback p_callback);

        /**
        * Add a function callback to this event
        * Also return the ID of the new listener (You should store the returned ID if you want to remove the listener later)
        * @param p_callback
        */
        ListenerID operator+=(Callback p_callback);

        /**
        * Remove a function callback to this event using a Listener (Created when calling AddListener)
        * @param p_listenerID
        */
        bool RemoveListener(ListenerID p_listenerID);

        /**
        * Remove a function callback to this event using a Listener (Created when calling AddListener)
        * @param p_listenerID
        */
        bool operator-=(ListenerID p_listenerID);

        /**
        * Remove every listeners to this event
        */
        void RemoveAllListeners();

        /**
        * Return the number of callback registered
        */
        uint64_t GetListenerCount();

        /**
        * Call every callbacks attached to this event
        * @param p_args (Variadic)
        */
        void Invoke(Args... p_args);

    private:
        std::unordered_map<ListenerID, Callback> m_callbacks;
        ListenerID m_availableListenerID = 0;
    };

} // namespace Lunaria::Eventing
