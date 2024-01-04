#ifndef PONCHAT_UTILS_CONSOLEINPUT_H_
#define PONCHAT_UTILS_CONSOLEINPUT_H_

#include <iostream>

namespace pon_chat::utils::console_input {

template <typename T>
T ReadNumber(const std::string& prompt, const std::string& error_message);

}  // namespace pon_chat::utils::console_input

#include "utils/src/console_input_impl.h"

#endif  // PONCHAT_UTILS_CONSOLEINPUT_H_
