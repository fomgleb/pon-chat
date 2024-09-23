#ifndef PONCHAT_EVENTS_EVENTSIMPL_H_
#define PONCHAT_EVENTS_EVENTSIMPL_H_

#include "pon-chat/events/events.h"

namespace pon_chat::events {

template <typename... Args>
void Event<Args...>::Subscribe(const std::function<void(Args...)> subscriber) {
  subscribers_.push_back(subscriber);
}

template <typename... Args>
void Event<Args...>::Invoke(Args... args) {
  for (const auto& subscriber : subscribers_) {
    subscriber(args...);
  }
}

}  // namespace pon_chat::events

#endif  // PONCHAT_EVENTS_EVENTSIMPL_H_
