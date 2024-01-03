#include "utils/inc/global_room_protocol.h"

namespace pon_chat::utils::global_room_protocol {

namespace msock = MinimalSocket;

void SendMessage(MinimalSocket::Sender& sender,
                 const std::string& message_sender_name,
                 const std::string& message_text) {
  uint32_t message_sender_name_size = htonl(message_sender_name.size());
  uint32_t message_text_size = htonl(message_text.size());

  std::string protocol_message;
  protocol_message.append(reinterpret_cast<char*>(&message_sender_name_size),
                          sizeof(message_sender_name_size));
  protocol_message.append(message_sender_name);
  protocol_message.append(reinterpret_cast<char*>(&message_text_size),
                          sizeof(message_text_size));
  protocol_message.append(message_text);

  sender.send(protocol_message);
}

void SendMessage(msock::Sender& sender, const Message& message) {
  SendMessage(sender, message.sender_name, message.text);
}

uint32_t bytes_to_uint32(const std::string& bytes) {
  uint32_t result = 0;
  std::copy_n(reinterpret_cast<const uint8_t*>(bytes.data()), sizeof(result),
              reinterpret_cast<uint8_t*>(&result));
  return ntohl(result);
}

std::optional<Message> ReceiveMessage(msock::Receiver& receiver) {
  Message received_message;

  try {
    uint32_t message_sender_name_size =
        bytes_to_uint32(receiver.receive(sizeof(uint32_t)));
    received_message.sender_name = receiver.receive(message_sender_name_size);
    uint32_t message_text_size =
        bytes_to_uint32(receiver.receive(sizeof(uint32_t)));
    received_message.text = receiver.receive(message_text_size);
  } catch (const msock::SocketError& e) {
    return std::nullopt;
  }

  return received_message;
}

}  // namespace pon_chat::utils::global_room_protocol
