#include "server/inc/global_room.h"

namespace pon_chat::server {

namespace msock = MinimalSocket;
namespace grp = utils::global_room_protocol;

void GlobalRoom::AcceptConnections() {
  while (true) {
    msock::tcp::TcpConnectionBlocking new_connection =
        tcp_server_->acceptNewClient();
    std::unique_lock<std::mutex> lock(connections_mutex_);
    connections_.push_back(std::make_shared<msock::tcp::TcpConnectionBlocking>(
        std::move(new_connection)));
    auto last_connection = connections_.back();
    lock.unlock();
    std::cout << last_connection->getRemoteAddress().getHost()
              << " joined the global room." << std::endl;

    std::thread start_handling_participant_messages_thread(
        &GlobalRoom::StartHandlingParticipantMessages, this, last_connection);
    start_handling_participant_messages_thread.detach();
  }
}

void GlobalRoom::StartHandlingParticipantMessages(
    std::shared_ptr<msock::tcp::TcpConnectionBlocking> connection) {
  while (true) {
    std::optional<grp::Message> maybe_message =
        grp::ReceiveMessage(*connection);

    std::unique_lock<std::mutex> lock(connections_mutex_);
    if (maybe_message.has_value()) {
      for (auto const& i : connections_) {
        if (connection == i) {
          continue;
        }
        grp::TrySendMessage(*i, maybe_message.value());
      }
      lock.unlock();
      std::cout << maybe_message.value().sender_name << ": "
                << maybe_message.value().text << std::endl;
    } else {
      connections_.remove(connection);
      lock.unlock();
      std::cout << connection->getRemoteAddress().getHost()
                << " left the global room." << std::endl;
      return;
    }
  }
}

void GlobalRoom::Start(const msock::Port listening_port) {
  tcp_server_ = std::make_unique<msock::tcp::TcpServer<true>>(listening_port);
  bool socket_is_opened = tcp_server_->open();

  std::thread accept_connections_thread(&GlobalRoom::AcceptConnections, this);

  accept_connections_thread.join();
}

}  // namespace pon_chat::server
