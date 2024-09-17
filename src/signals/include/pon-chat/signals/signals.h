#ifndef PONCHAT_SIGNALS_SIGNALS_H_
#define PONCHAT_SIGNALS_SIGNALS_H_

#include <cerrno>
#include <csignal>
#include <cstring>
#include <iostream>

namespace pon_chat::signals {

sighandler_t GetAndSetSighandler(const int signal,
                                 const sighandler_t new_sighandler);

}

#endif  // PONCHAT_SIGNALS_SIGNALS_H_
