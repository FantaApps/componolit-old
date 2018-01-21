#include <libc/component.h>
#include <base/log.h>
#include <timer_session/connection.h>

#include <thread>
#include <mutex>

volatile unsigned shared = 0;
std::mutex mtx;

static void test()
{
    Genode::log("Thread executed");
    std::lock_guard<std::mutex> guard(mtx);
    shared = 1;
    Genode::log("Thread done");
}

struct Main {

    Timer::Connection _timer;

    Main(Genode::Env &env) : _timer(env)
    {
        Genode::log("Main executed");

        cxxthread_env.initialize (env, 10 * 4096);

        mtx.lock();
        std::thread t(test);

        if (shared == 1)
        {
            // We hold the lock - thread should not modify shared variable if
            // lock guard works
            Genode::log("Lock_guard FAILED");
            return;
        }
        mtx.unlock();

        // Wait for thread to acquire lock
        _timer.msleep(1000);

        mtx.lock();
        // We would not get this lock of lock guard does not work
        Genode::log("Lock_guard OK");
        mtx.unlock();

        t.join();
    }
};

void Libc::Component::construct(Libc::Env &env)
{
   static Main main(env);
}
