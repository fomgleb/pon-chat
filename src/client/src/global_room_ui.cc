#include "global_room_ui.h"

namespace pon_chat::client {

namespace grp = pon_chat::utils::global_room_protocol;
namespace msock = MinimalSocket;

void GlobalRoom::SendMessageAndAddToMessageElements(grp::Message& message) {
  message_elements.push_back(ftxui::window(ftxui::text(message.sender_name),
                                           ftxui::paragraph(message.text)));
  chat_screen_.PostEvent(ftxui::Event::Custom);
}

ftxui::Component GlobalRoom::CreateMessangerRenderer() {
  auto message_input_field_option = ftxui::InputOption();
  message_input_field_option.on_enter = [&] {
    if (message_input_field_text_ == "\n") {
      return;
    }
    grp::Message message{user_name_input_field_text_.substr(
                             0, user_name_input_field_text_.size() - 1),
                         message_input_field_text_.substr(
                             0, message_input_field_text_.size() - 1)};

    if (!grp::TrySendMessage(tcp_client_, message)) {
      error_message_ = "Lost connection with the server";
      chat_screen_.Exit();
      return;
    }

    SendMessageAndAddToMessageElements(message);
    message_input_field_text_ = "";
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

ftxui::Component GlobalRoom::CreateLoginRenderer() {
  auto login_input_field_option = ftxui::InputOption();
  login_input_field_option.on_enter = [&] {
    login_screen_.Exit();
    chat_screen_.Loop(messenger_renderer_);
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

GlobalRoom::GlobalRoom(msock::tcp::TcpClient<true>& opened_tcp_client)
    : tcp_client_(opened_tcp_client) {}

void GlobalRoom::StartLoop() {
  messenger_renderer_ = CreateMessangerRenderer();
  ftxui::Component login_renderer = CreateLoginRenderer();

  std::thread handle_messages_from_server_thread([&] {
    while (true) {
      std::optional<grp::Message> received_message =
          grp::ReceiveMessage(tcp_client_);
      if (!received_message.has_value()) {
        error_message_ = "Lost connection with the server";
        chat_screen_.Exit();
        break;
      }
      SendMessageAndAddToMessageElements(received_message.value());
    }
  });

  handle_messages_from_server_thread.detach();
  login_screen_.Loop(login_renderer);
  std::cerr << error_message_ << std::endl;
}

}  // namespace pon_chat::client
