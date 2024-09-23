#ifndef PONCHAT_EVENTS_EVENTS_H_
#define PONCHAT_EVENTS_EVENTS_H_

#include <functional>
#include <vector>

namespace pon_chat::events {

template <typename... Args>
class Event {
 private:
  std::vector<std::function<void(Args...)>> subscribers_;

 public:
  void Subscribe(const std::function<void(Args...)> subscriber);
  void Invoke(Args... args);
};

}  // namespace pon_chat::events

#include "../../../src/events_impl.h"

#endif  // PONCHAT_EVENTS_EVENTS_H_
