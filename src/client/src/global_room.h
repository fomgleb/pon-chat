#ifndef PONCHAT_CLIENT_GLOBALROOM_H_
#define PONCHAT_CLIENT_GLOBALROOM_H_

#include "pon-chat/ui/global_room_ui.h"
#include "MinimalSocket/tcp/TcpClient.h"

namespace pon_chat::client {

class GlobalRoom {
 private:
  MinimalSocket::tcp::TcpClient<true>& tcp_client_;
  ui::GlobalRoomUI ui_;
  std::string error_message_;
  std::string username_;

  void OnEnteredUsername(const std::string& username);
  void OnEnteredMessage(const std::string& message_text);

 public:
  GlobalRoom(MinimalSocket::tcp::TcpClient<true>& opened_tcp_client);
  void StartLoop();
};

}  // namespace pon_chat::client

#endif  // PONCHAT_CLIENT_GLOBALROOM_H_
