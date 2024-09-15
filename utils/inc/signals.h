#ifndef PONCHAT_UTILS_SIGNALS_H_
#define PONCHAT_UTILS_SIGNALS_H_

#include <cerrno>
#include <csignal>
#include <cstring>
#include <iostream>

namespace pon_chat::utils::signals {

sighandler_t GetAndSetSighandler(const int signal,
                                 const sighandler_t new_sighandler);

}

#endif  // PONCHAT_UTILS_SIGNALS_H_
