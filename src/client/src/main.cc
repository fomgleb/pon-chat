#include "global_room.h"
#include "pon-chat/console_input/console_input.h"
#include "pon-chat/ui/global_room_graphical_ui.h"

namespace msock = MinimalSocket;
namespace ci = pon_chat::console_input;
namespace client = pon_chat::client;

int main() {
  std::string server_ip = ci::ReadString("Enter server IP: ");
  uint16_t server_port =
      ci::ReadNumber<uint16_t>("Enter server port: ", "Incorrect format!");
  msock::Address server_address(server_ip, server_port);
  msock::tcp::TcpClient<true> tcp_client(server_address);

  tcp_client.open();

  pon_chat::ui::GlobalRoomGraphicalUI ui;

  client::GlobalRoom global_room(tcp_client, ui);

  global_room.StartLoop();

  return 0;
}
