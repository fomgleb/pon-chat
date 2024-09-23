#ifndef PONCHAT_UI_GLOBALROOMUI_H_
#define PONCHAT_UI_GLOBALROOMUI_H_

#include "ftxui/component/component.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "pon-chat/events/events.h"
#include "pon-chat/protocols/global_room_protocol.h"

#include <future>

namespace pon_chat::ui {

class GlobalRoomUI {
 private:
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
  events::Event<const std::string&> enteredUserNameEvent;
  events::Event<const std::string&> enteredMessageEvent;

  void StartLoginScreen();
  void StartChatScreen();
  void StopLoginScreen();
  void StopChatScreen();

  void AddAndDrawNewMessage(protocols::global_room_protocol::Message& message);
  void ClearMessageInputField();
};

}  // namespace pon_chat::ui

#endif  // PONCHAT_UI_GLOBALROOMUI_H_
