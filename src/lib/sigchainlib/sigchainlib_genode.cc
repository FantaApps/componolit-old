#include <base/log.h>
#include "sigchain.h"

#define ATTRIBUTE_UNUSED __attribute__((__unused__))

namespace art {


extern "C" void ClaimSignalChain(int signal ATTRIBUTE_UNUSED,
                                 struct sigaction* oldaction ATTRIBUTE_UNUSED) {
	Genode::warning(__func__, " not implemented");
}

extern "C" void UnclaimSignalChain(int signal ATTRIBUTE_UNUSED) {
	Genode::warning(__func__, " not implemented");
}

extern "C" void InvokeUserSignalHandler(int sig ATTRIBUTE_UNUSED,
                                        siginfo_t* info ATTRIBUTE_UNUSED,
                                        void* context ATTRIBUTE_UNUSED) {
	Genode::warning(__func__, " not implemented");
}

extern "C" void InitializeSignalChain() {
	Genode::warning(__func__, " not implemented");
}

extern "C" void EnsureFrontOfChain(int signal ATTRIBUTE_UNUSED,
                                   struct sigaction* expected_action ATTRIBUTE_UNUSED) {
	Genode::warning(__func__, " not implemented");
}
}