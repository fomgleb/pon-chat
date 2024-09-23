#include "global_room.h"

namespace pon_chat::client {

namespace grp = pon_chat::protocols::global_room_protocol;
namespace msock = MinimalSocket;

void GlobalRoom::OnEnteredUsername(const std::string& username) {
  username_ = username;
  ui_.StopLoginScreen();
  ui_.StartChatScreen();
}

void GlobalRoom::OnEnteredMessage(const std::string& message_text) {
  if (message_text == "\n") {
    return;
  }

  grp::Message message{username_.substr(0, username_.size() - 1),
                       message_text.substr(0, message_text.size() - 1)};
  if (!grp::TrySendMessage(tcp_client_, message)) {
    error_message_ = "Lost connection with the server";
    ui_.StopChatScreen();
    return;
  }
  ui_.AddAndDrawNewMessage(message);
  ui_.ClearMessageInputField();
}

GlobalRoom::GlobalRoom(msock::tcp::TcpClient<true>& opened_tcp_client)
    : tcp_client_(opened_tcp_client) {
  ui_.enteredUserNameEvent.Subscribe(
      std::bind(&GlobalRoom::OnEnteredUsername, this, std::placeholders::_1));
  ui_.enteredMessageEvent.Subscribe(
      std::bind(&GlobalRoom::OnEnteredMessage, this, std::placeholders::_1));
}

void GlobalRoom::StartLoop() {
  std::thread handle_messages_from_server_thread([&] {
    while (true) {
      std::optional<grp::Message> received_message =
          grp::ReceiveMessage(tcp_client_);
      if (!received_message.has_value()) {
        error_message_ = "Lost connection with the server";
        ui_.StopChatScreen();
        break;
      }
      ui_.AddAndDrawNewMessage(received_message.value());
    }
  });
  handle_messages_from_server_thread.detach();

  ui_.StartLoginScreen();

  std::cerr << error_message_ << std::endl;
}

}  // namespace pon_chat::client
