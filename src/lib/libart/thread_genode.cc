#include <base/log.h>

#include "thread.h"

namespace art {

void Thread::SetUpAlternateSignalStack() {
	Genode::log(__func__, ": Not implemented");
}
void Thread::TearDownAlternateSignalStack() {
	Genode::log(__func__, ": Not implemented");
}

void Thread::SetNativePriority(int) {
	Genode::log(__func__, ": Not implemented");
	// Do nothing.
}

int Thread::GetNativePriority() {                                                                                                              
	Genode::log(__func__, ": Not implemented");
	return kNormThreadPriority;
}

}
