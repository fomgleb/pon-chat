#ifndef PONCHAT_SERVER_GLOBALROOM_H_
#define PONCHAT_SERVER_GLOBALROOM_H_

#include <iostream>
#include <list>
#include <thread>

#include "MinimalSocket/tcp/TcpServer.h"
#include "utils/inc/global_room_protocol.h"

namespace pon_chat::server {

class GlobalRoom {
 private:
  std::unique_ptr<MinimalSocket::tcp::TcpServer<true>> tcp_server_;
  std::list<std::shared_ptr<MinimalSocket::tcp::TcpConnectionBlocking>>
      connections_;
  std::mutex connections_mutex_;
  void AcceptConnections();
  void StartHandlingParticipantMessages(
      std::shared_ptr<MinimalSocket::tcp::TcpConnectionBlocking> connection);

 public:
  void Start(const MinimalSocket::Port listening_port);
};

}  // namespace pon_chat::server

#endif  // PONCHAT_SERVER_GLOBALROOM_H_
