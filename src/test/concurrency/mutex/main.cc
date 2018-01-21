#include <libc/component.h>
#include <base/log.h>
#include <timer_session/connection.h>

#include <thread>
#include <mutex>

std::mutex mtx;
volatile static int shared = 0;

static void test()
{
    mtx.lock();
    shared = 1;
    Genode::log("Thread executed");
    mtx.unlock();
}

struct Main {

    Timer::Connection _timer;

    Main(Genode::Env &env) : _timer(env)
    {
        cxxthread_env.initialize (env, 10 * 4096);
        mtx.lock();
        std::thread t(test);

        // Wait for thread to set shared variable
        _timer.msleep(1000);
        if (shared == 1)
        {
            Genode::log("Mutex FAILED");
            return;
        }

        mtx.unlock();
        t.join();
        Genode::log("Mutex OK");
    }
};

void Libc::Component::construct(Libc::Env &env)
{
   static Main main(env);
}
