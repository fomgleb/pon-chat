#ifndef PONCHAT_SIGNALS_SIGNALS_H_
#define PONCHAT_SIGNALS_SIGNALS_H_

#include <cerrno>
#include <csignal>
#include <cstring>
#include <iostream>

namespace pon_chat::signals {

#ifdef _WIN32
using sighandler_t = void(__cdecl*)(int);
#else
#ifndef sighandler_t
using sighandler_t = void (*)(int);
#endif
#endif

sighandler_t GetAndSetSighandler(const int signal_number,
                                 const sighandler_t new_sighandler);

}  // namespace pon_chat::signals

#endif  // PONCHAT_SIGNALS_SIGNALS_H_
