#ifndef PONCHAT_CLIENT_GLOBALROOMUI_H
#define PONCHAT_CLIENT_GLOBALROOMUI_H

#include "MinimalSocket/tcp/TcpClient.h"
#include "ftxui/component/component.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "pon-chat/utils/global_room_protocol.h"

#include <future>

namespace pon_chat::client {

class GlobalRoom {
 private:
  MinimalSocket::tcp::TcpClient<true>& tcp_client_;

  ftxui::ScreenInteractive chat_screen_ =
      ftxui::ScreenInteractive::Fullscreen();
  ftxui::ScreenInteractive login_screen_ =
      ftxui::ScreenInteractive::FitComponent();

  ftxui::Component login_input_field_;

  std::string user_name_input_field_text_;

  ftxui::Component message_input_field_;
  std::string message_input_field_text_;

  ftxui::Elements message_elements;

  ftxui::Component messenger_renderer_;

  std::string error_message_ = "";

  void SendMessageAndAddToMessageElements(
      pon_chat::utils::global_room_protocol::Message& message);
  ftxui::Component CreateMessangerRenderer();
  ftxui::Component CreateLoginRenderer();

 public:
  GlobalRoom(MinimalSocket::tcp::TcpClient<true>& opened_tcp_client);
  void StartLoop();
};

}  // namespace pon_chat::client

#endif  // PONCHAT_CLIENT_GLOBALROOMUI_H
