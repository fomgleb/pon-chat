#include "server/inc/global_room.h"
#include "utils/inc/console_input.h"

namespace console_input = pon_chat::utils::console_input;
namespace msock = MinimalSocket;

int main() {
  pon_chat::server::GlobalRoom global_room;

  auto listening_port = console_input::ReadNumber<msock::Port>(
      "Enter a port to listen: ", "Invalid input");

  global_room.Start(listening_port);

  return 0;
}
