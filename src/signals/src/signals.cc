#include "pon-chat/signals/signals.h"

namespace pon_chat::signals {

sighandler_t GetAndSetSighandler(const int signal_number,
                                 const sighandler_t new_sighandler)
{
#ifdef _WIN32
    sighandler_t old_handler = signal(signal_number, new_sighandler);
    if (old_handler == SIG_ERR) {
        std::cerr << "Failed to set the signal handler "
                  << reinterpret_cast<void*>(new_sighandler) << " for signal "
                  << signal_number << ". Error: " << strerror(errno)
                  << std::endl;
        exit(EXIT_FAILURE);
    }
    return old_handler;
#else
    struct sigaction old_action;
    struct sigaction new_action;
    std::memset(&new_action, 0, sizeof(new_action));
    new_action.sa_handler = new_sighandler;
    if (sigaction(signal_number, &new_action, &old_action) == -1) {
        std::cerr << "Failed to set the signal handler "
                  << reinterpret_cast<void*>(new_sighandler) << " for signal "
                  << signal_number << ". Error: " << strerror(errno)
                  << std::endl;
        exit(EXIT_FAILURE);
    }
    return old_action.sa_handler;
#endif
}

}  // namespace pon_chat::signals
