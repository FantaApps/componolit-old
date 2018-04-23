#include <stdlib.h>
#include <err.h>

#include <sys/mman.h>
#include <libc/component.h>

void Libc::Component::construct(Libc::Env &env)
{
    bool failed = false;
    using namespace Genode;

    enum { ITERS = 4, SIZE = 42, ALIGN = 4096, ADDR = 0xc0de000000};

    Libc::with_libc([&] {

        for (int i = 0; i < ITERS; i++)
        {
	        void *addr = mmap((void *)ADDR, SIZE, PROT_READ, MAP_ANON, -1, 0);
            if (addr == (void *)-1)
            {
                failed |= true;
                Genode::error("#", i, " mmap failed: addr=", addr);
            } else {
                if (ADDR && (addr != (void *)ADDR))
                {
                    failed |= true;
                    Genode::error("#", i, " invalid address: expected:", (void *)ADDR, " got:", addr);
                }
                if (munmap(addr, SIZE) < 0)
                {
                    Genode::error("#", i, " munmap failed for addr ", (void *)ADDR);
                };
            }
        }

        exit (failed ? 1 : 0);
    });
}
