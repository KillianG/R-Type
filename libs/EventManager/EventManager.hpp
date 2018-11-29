#pragma once

#include <memory>
#include <algorithm>
#include <functional>
#include <unordered_map>
#include <algorithm>
#include "Receiver.hpp"
#include "BaseEvent.hpp"
#include "ClassTypeId.hpp"

/**
 * @brief CallBack Wrapper
 */
class BaseCallbackWrapper {
public:
    virtual ~BaseCallbackWrapper() noexcept = default;

    virtual void operator()(const BaseEvent *event) const noexcept = 0;
};

template<typename EventType>
class callbackWrapper : public BaseCallbackWrapper {
public:
    explicit callbackWrapper(const std::function<void(const EventType &)> &callBack) noexcept : _callback(std::move(callBack)) {}

    void operator()(const BaseEvent *event) const noexcept {
        /**
         * Call the _callback function
         */
        _callback(*(static_cast<const EventType *>(event)));
    }

private:
    std::function<void(const EventType &)> _callback;
};

/**
 * EventManager
 */
class EventManager {
public:
    explicit EventManager() = default;

    /**
     * @brief Subscribe a receiver to a certain type of event
     *
     * All those who have subscribed to this event will receive it
     * @tparam EventType
     * @param receiver
     * @see Receiver(Receiver.hpp)
     */
    template<typename EventType, typename Receiver>
    void subscribe(Receiver &receiver) noexcept {
        static_assert(std::is_base_of<BaseEvent, EventType>(), "Templated parameter is not based of BaseEvent");
        const auto eventType = ClassTypeId<BaseEvent>::getTypeId<EventType>();
        const Receiver &baseReceiver = receiver;
        /**
         * Lambda calls the receiver.receive(<ev>) member function
         * The function must be implemented to the current receiver
         */
        auto receiverCallback = [&receiver](const auto &ev) noexcept { receiver.receive(ev); };
        auto callbackPtr = std::make_unique<callbackWrapper<EventType>>(std::move(receiverCallback));
        _receiversList.emplace(eventType, ReceiverInfo{&baseReceiver, std::move(callbackPtr)});
    }

    /**
     *@brief Unsubscribe a receiver to a certain type of event
     * @tparam EventType
     * @param receiver
     */
    template<typename EventType, typename Receiver>
    void unsubscribe(Receiver &receiver) noexcept {
        static_assert(std::is_base_of<BaseEvent, EventType>(), "Templated parameter is not based of BaseEvent");
        /**
         * std::unordered_multimap::equal_range()
         * Return range of elements matching a specific key (EventType'id from BaseEvent's group)
         */
        auto &&receivers = _receiversList.equal_range(ClassTypeId<BaseEvent>::getTypeId<EventType>());
        for (auto &it = receivers.first; it != receivers.second;) {
            if (it->second.receiver == &receiver)
                it = _receiversList.erase(it);
            else
                it++;
        }
    }

    /**
     * @brief Unsubscribe a receiver to all type of event
     * @tparam Receiver
     * @param receiver
     */
    template<typename Receiver>
    void unsubscribeAll(Receiver &receiver) noexcept {
        for (auto it = _receiversList.begin(); it != _receiversList.end();) {
            if (it->second.receiver == &receiver)
                it = _receiversList.erase(it);
            else
                it++;
        }
    }

    /**
     * @brief Unsubscribe a receiver to all type of event
     * @tparam Receiver
     * @param receiver
     */
    void unsubscribeAll() noexcept {
        _receiversList.clear();
    }

    /**
     * @brief Emit a certain type of event
     * @tparam EventType The event you want to emit
     * @param params Parameters of the event's ctor
     */
    template<typename EventType, typename ... Params>
    void emit(Params &&... params) noexcept {
        static_assert(std::is_base_of<BaseEvent, EventType>(), "Templated parameter is not based of BaseEvent");
        /**
         * Event's ctor
         */
        EventType event{std::forward<Params>(params)...};
        /**
         * std::unordered_multimap::equal_range()
         * Return range of elements matching a specific key (EventType's id from the group BaseEvent)
         */
        auto &&receivers = _receiversList.equal_range(ClassTypeId<BaseEvent>::getTypeId<EventType>());
        /**
         * Call each receiver::receive(<Event>) member function via the lambda
         * @see BaseCallbackWrapper::operator()(const BaseEvent *event)
         */
        std::for_each(receivers.first, receivers.second, [&event](const auto &receiverInfo) noexcept { (*receiverInfo.second.callbackPtr)(&event); });
    }

private:
    /**
     * It sucks using std::pair
     */
    struct ReceiverInfo {
        const BaseReceiver *receiver;
        std::unique_ptr<BaseCallbackWrapper> callbackPtr;
    };

    /**
     * It will have multiple keys
     * Event's id will be from ClassTypeId<Group(BaseEvent)>
     */
    std::unordered_multimap<ClassTypeId<BaseEvent>::TypeId, ReceiverInfo> _receiversList{};
};
