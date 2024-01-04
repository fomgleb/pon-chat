#ifndef PONCHAT_UTILS_CONSOLEINPUTIMPL_H_
#define PONCHAT_UTILS_CONSOLEINPUTIMPL_H_

#include "utils/inc/console_input.h"

namespace pon_chat::utils::console_input {

template <typename T>
T ReadNumber(const std::string& prompt, const std::string& error_message) {
  static_assert(std::is_arithmetic<T>::value, "T must be a numeric type");

  T parsed_input;
  std::string input;
  while (true) {
    std::cout << prompt;
    std::getline(std::cin, input);
    std::istringstream iss(input);
    if (iss >> parsed_input) {
      break;
    } else {
      std::cerr << error_message << std::endl;
    }
  }
  return parsed_input;
}

}  // namespace pon_chat::utils::console_input

#endif  // PONCHAT_UTILS_CONSOLEINPUTIMPL_H_
