#ifndef PONCHAT_UI_GLOBALROOMCONSOLEUI_H_
#define PONCHAT_UI_GLOBALROOMCONSOLEUI_H_

#include "ftxui/component/component.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "global_room_ui.h"
#include "pon-chat/events/events.h"

namespace pon_chat::ui {

class GlobalRoomConsoleUI : public GlobalRoomUI {
 private:
  events::Event<const std::string&> enteredUserNameEvent;
  events::Event<const std::string&> enteredMessageEvent;

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
  void SubscribeToEnteredUserNameEvent(
      std::function<void(const std::string& username)> func) override;
  void SubscribeToEnteredMessageEvent(
      std::function<void(const std::string& message)> func) override;

  void StartLoginScreen() override;
  void StartChatScreen() override;
  void StopLoginScreen() override;
  void StopChatScreen() override;

  void AddAndDrawNewMessage(
      protocols::global_room_protocol::Message& message) override;
  void ClearMessageInputField() override;
};

}  // namespace pon_chat::ui

#endif  // PONCHAT_UI_GLOBALROOMCONSOLEUI_H_
