
#include <libc/component.h>
#include <base/log.h>

#include <thread>

static void test()
{
    Genode::log("threads tls: ", __func__);
    __thread int _x = 42;
    int x = _x;
    void* x_ptr = (void*)&_x;
    Genode::log("concurrency tls: ", x, " @ ", x_ptr);
}

struct Main{
    
    Main(Genode::Env &)
    {
        Genode::log("concurrency tls: ", __func__);
        std::thread t(test);
        for(;;);
    }
};

void Libc::Component::construct(Libc::Env &env)
{
   static Main main(env); 
}
