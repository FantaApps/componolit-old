#include <thread>

std::thread_env cxxthread_env;

extern "C" void *__emutls_get_address (void *)
{
    throw std::tls_not_implemented();
}
