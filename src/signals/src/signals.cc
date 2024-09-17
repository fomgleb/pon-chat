#include "pon-chat/signals/signals.h"

namespace pon_chat::signals {

sighandler_t GetAndSetSighandler(const int signal,
                                 const sighandler_t new_sighandler) {
  struct sigaction old_action;
  struct sigaction new_action;
  std::memset(&new_action, 0, sizeof(new_action));
  new_action.sa_handler = new_sighandler;
  if (sigaction(signal, &new_action, &old_action) == -1) {
    std::cerr << "Failed to set the signal handler " << new_sighandler
              << " for signal " << signal << ". Error: " << strerror(errno)
              << std::endl;
    exit(EXIT_FAILURE);
  }
  return old_action.sa_handler;
}

}  // namespace pon_chat::signals
