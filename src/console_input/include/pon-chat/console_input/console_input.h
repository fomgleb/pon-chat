#ifndef PONCHAT_CONSOLEINPUT_CONSOLEINPUT_H_
#define PONCHAT_CONSOLEINPUT_CONSOLEINPUT_H_

#include <string>

namespace pon_chat::console_input {

template <typename T>
T ReadNumber(const std::string& prompt, const std::string& error_message);
std::string ReadString(const std::string& prompt);

}  // namespace pon_chat::console_input

#include "../../../src/console_input_impl.h"

#endif  // PONCHAT_CONSOLEINPUT_CONSOLEINPUT_H_
