#ifndef PONCHAT_CLIENT_GLOBALROOMUI_H
#define PONCHAT_CLIENT_GLOBALROOMUI_H

#include "MinimalSocket/tcp/TcpClient.h"
#include "ftxui/component/component.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "pon-chat/protocols/global_room_protocol.h"

#include <future>

namespace pon_chat::client {

class GlobalRoomUI {
 private:
  std::vector<std::function<void(const std::string&)>>
      subs_for_entered_username_event;
  void InvokeEnteredUsernameEvent(const std::string& username);

  std::vector<std::function<void(const std::string&)>>
      subs_for_entered_message_event;
  void InvokeEnteredMessageEvent(const std::string& message);

  ftxui::ScreenInteractive chat_screen_ =
      ftxui::ScreenInteractive::Fullscreen();
  ftxui::ScreenInteractive login_screen_ =
      ftxui::ScreenInteractive::FitComponent();

  ftxui::Component login_input_field_;
  std::string user_name_input_field_text_;

  ftxui::Component message_input_field_;
  std::string message_input_field_text_;

  ftxui::Elements message_elements;

  ftxui::Component CreateMessangerRenderer();
  ftxui::Component CreateLoginRenderer();

 public:
  void SubscribeForEnteredUsernameEvent(
      const std::function<void(const std::string&)>& sub);
  void SubscribeForEnteredMessageEvent(
      const std::function<void(const std::string&)>& sub);

  void StartLoginScreen();
  void StartChatScreen();
  void StopLoginScreen();
  void StopChatScreen();

  void AddAndDrawNewMessage(protocols::global_room_protocol::Message& message);
  void ClearMessageInputField();
};

}  // namespace pon_chat::client

#endif  // PONCHAT_CLIENT_GLOBALROOMUI_H
