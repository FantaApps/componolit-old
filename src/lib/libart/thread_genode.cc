#include <base/log.h>

#include "thread.h"

namespace art {

void Thread::SetUpAlternateSignalStack() {
	Genode::warning(__func__, ": Not implemented");
}
void Thread::TearDownAlternateSignalStack() {
	Genode::warning(__func__, ": Not implemented");
}

void Thread::SetNativePriority(int) {
	Genode::warning(__func__, ": Not implemented");
}

int Thread::GetNativePriority() {                                                                                                              
	Genode::warning(__func__, ": Not implemented");
	return kNormThreadPriority;
}

void Thread::InitCpu() {
	Genode::warning(__func__, ": Not implemented");
}

void Thread::CleanupCpu() {
	Genode::warning(__func__, ": Not implemented");
}

}
