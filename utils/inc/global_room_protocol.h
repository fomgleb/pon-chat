#ifndef PONCHAT_UTILS_GLOBALROOMPROTOCOL_H_
#define PONCHAT_UTILS_GLOBALROOMPROTOCOL_H_

#include <MinimalSocket/core/Receiver.h>
#include <MinimalSocket/core/Sender.h>

#include <algorithm>

#ifdef _WIN32
#include <winsock2.h>  // For Windows
#else
#include <arpa/inet.h>  // For Unix
#endif

namespace pon_chat::utils::global_room_protocol {

struct Message {
  std::string sender_name;
  std::string text;
};

void SendMessage(MinimalSocket::Sender& sender,
                 const std::string& message_sender_name,
                 const std::string& message_text);
void SendMessage(MinimalSocket::Sender& sender, const Message& message);
Message ReceiveMessage(MinimalSocket::Receiver& receiver);

}  // namespace pon_chat::utils::global_room_protocol

#endif  // PONCHAT_UTILS_GLOBALROOMPROTOCOL_H_
