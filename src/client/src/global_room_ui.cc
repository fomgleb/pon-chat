#include "global_room_ui.h"

namespace pon_chat::client {

namespace grp = pon_chat::protocols::global_room_protocol;
namespace msock = MinimalSocket;

void GlobalRoomUI::InvokeEnteredUsernameEvent(const std::string& username) {
  for (auto const& sub : subs_for_entered_username_event) {
    sub(username);
  }
}

void GlobalRoomUI::InvokeEnteredMessageEvent(const std::string& message) {
  for (auto const& sub : subs_for_entered_message_event) {
    sub(message);
  }
}

ftxui::Component GlobalRoomUI::CreateMessangerRenderer() {
  auto message_input_field_option = ftxui::InputOption();
  message_input_field_option.on_enter = [&] {
    InvokeEnteredMessageEvent(message_input_field_text_);
  };
  message_input_field_ = ftxui::Component(
      ftxui::Input(&message_input_field_text_, "Enter your message...",
                   message_input_field_option));

  auto messanger_renderer = ftxui::Renderer(message_input_field_, [&] {
    return ftxui::vbox({
               ftxui::vbox({message_elements}) | ftxui::vscroll_indicator |
                   ftxui::focusPositionRelative(0, 1) | ftxui::yframe |
                   ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, 40),
               ftxui::separator(),
               message_input_field_->Render() |
                   ftxui::size(ftxui::HEIGHT, ftxui::GREATER_THAN, 5),
           }) |
           ftxui::borderHeavy | ftxui::flex;
  });
  return messanger_renderer;
}

ftxui::Component GlobalRoomUI::CreateLoginRenderer() {
  auto login_input_field_option = ftxui::InputOption();
  login_input_field_option.on_enter = [&] {
    InvokeEnteredUsernameEvent(user_name_input_field_text_);
  };
  login_input_field_ =
      ftxui::Input(&user_name_input_field_text_, login_input_field_option);

  auto login_renderer = ftxui::Renderer(login_input_field_, [&] {
    return ftxui::vbox({
               ftxui::text("Введи своё имя:"),
               ftxui::separator(),
               login_input_field_->Render(),
           }) |
           ftxui::border | ftxui::center;
  });
  return login_renderer;
}

void GlobalRoomUI::SubscribeForEnteredUsernameEvent(
    const std::function<void(const std::string&)>& sub) {
  subs_for_entered_username_event.push_back(sub);
}

void GlobalRoomUI::SubscribeForEnteredMessageEvent(
    const std::function<void(const std::string&)>& sub) {
  subs_for_entered_message_event.push_back(sub);
}

void GlobalRoomUI::StartLoginScreen() {
  ftxui::Component login_renderer = CreateLoginRenderer();
  login_screen_.Loop(login_renderer);
}

void GlobalRoomUI::StartChatScreen() {
  ftxui::Component messenger_renderer = CreateMessangerRenderer();
  chat_screen_.Loop(messenger_renderer);
}

void GlobalRoomUI::StopLoginScreen() {
  login_screen_.Exit();
}

void GlobalRoomUI::StopChatScreen() {
  chat_screen_.Exit();
}

void GlobalRoomUI::AddAndDrawNewMessage(grp::Message& message) {
  message_elements.push_back(ftxui::window(ftxui::text(message.sender_name),
                                           ftxui::paragraph(message.text)));
  chat_screen_.PostEvent(ftxui::Event::Custom);
}

void GlobalRoomUI::ClearMessageInputField() {
  message_input_field_text_ = "";
}

}  // namespace pon_chat::client
