/* Genode includes */
#include <libc/component.h>

/* libc includes */
#include <stdlib.h> /* 'exit'   */
#include <stdio.h>
#include <pthread.h>

static void *cb (void *arg)
{
    printf("CB\n");
    return nullptr;
}

class Foo
{
    public:
        Foo()
        {
            printf("Foo\n");
            pthread_t pt;
            pthread_attr_t attr;
            pthread_attr_init (&attr);
            pthread_attr_setstacksize (&attr, 10000);
            pthread_create(&pt, &attr, &cb, nullptr);
            pthread_attr_destroy (&attr);
        }
};

void Libc::Component::construct(Libc::Env &env)
{
	Libc::with_libc([&env] {
        Foo *foo = new Foo();
		exit (0);
	});
}
