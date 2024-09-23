#ifndef PONCHAT_PROTOCOLS_GLOBALROOMPROTOCOL_H_
#define PONCHAT_PROTOCOLS_GLOBALROOMPROTOCOL_H_

#include "MinimalSocket/core/Receiver.h"
#include "MinimalSocket/core/Sender.h"

#include <algorithm>

#include "pon-chat/signals/signals.h"

#ifdef _WIN32
#include <winsock2.h>  // For Windows
#else
#include <arpa/inet.h>  // For Unix
#endif

namespace pon_chat::protocols::global_room_protocol {

struct Message {
  std::string sender_name;
  std::string text;
};

bool TrySendMessage(MinimalSocket::Sender& sender,
                    const std::string& message_sender_name,
                    const std::string& message_text);
bool TrySendMessage(MinimalSocket::Sender& sender, const Message& message);
std::optional<Message> ReceiveMessage(MinimalSocket::Receiver<true>& receiver);

}  // namespace pon_chat::protocols::global_room_protocol

#endif  // PONCHAT_PROTOCOLS_GLOBALROOMPROTOCOL_H_
