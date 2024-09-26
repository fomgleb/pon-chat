#ifndef PONCHAT_UI_GLOBALROOMUI_H_
#define PONCHAT_UI_GLOBALROOMUI_H_

#include "pon-chat/protocols/global_room_protocol.h"

#include <future>

namespace pon_chat::ui {

class GlobalRoomUI {
 public:
  virtual ~GlobalRoomUI() = default;

  virtual void SubscribeToEnteredUserNameEvent(
      std::function<void(const std::string& username)> func) = 0;
  virtual void SubscribeToEnteredMessageEvent(
      std::function<void(const std::string& message)> func) = 0;

  virtual void StartLoginScreen() = 0;
  virtual void StartChatScreen() = 0;
  virtual void StopLoginScreen() = 0;
  virtual void StopChatScreen() = 0;

  virtual void AddAndDrawNewMessage(
      protocols::global_room_protocol::Message& message) = 0;
  virtual void ClearMessageInputField() = 0;
};

}  // namespace pon_chat::ui

#endif  // PONCHAT_UI_GLOBALROOMUI_H_
