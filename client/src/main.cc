#include "client/inc/global_room_ui.h"
#include "utils/inc/console_input.h"

namespace msock = MinimalSocket;
namespace ci = pon_chat::utils::console_input;
namespace client = pon_chat::client;

int main() {
  std::string server_ip = ci::ReadString("Enter server IP: ");
  uint16_t server_port =
      ci::ReadNumber<uint16_t>("Enter server port: ", "Incorrect format!");
  msock::Address server_address(server_ip, server_port);
  msock::tcp::TcpClient<true> tcp_client(server_address);

  tcp_client.open();

  client::GlobalRoom global_room(tcp_client);

  global_room.StartLoop();

  return 0;
}
