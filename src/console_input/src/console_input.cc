#include "pon-chat/console_input/console_input.h"

namespace pon_chat::console_input {

std::string ReadString(const std::string& prompt = "") {
  std::cout << prompt;
  std::string input;
  std::getline(std::cin, input);
  return input;
}

}  // namespace pon_chat::console_input
