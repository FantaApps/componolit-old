/* Genode includes */
#include <libc/component.h>

/* libc includes */
#include <stdlib.h> /* 'exit'   */
#include <stdio.h>
#include <string>

void Libc::Component::construct(Libc::Env &env)
{
	Libc::with_libc([&env] {

        // WORKS
        // /tmp/art-data-2uQgxL

        // FAILS
        // /tmp/art-data-wuebBI
        // /tmp/art-data-ha5fue
        // /tmp/art-data-yFj9bR
        // /tmp/art-data-7uQEtf
        //
        std::string path = "/tmp/art-data-m5x4OJ";
        path += "/TmpFile-XXXXXX";

        for (int i = 0; i < 100; i++)
        {
            mkstemp(&path[0]);
            printf("path %d: %s XXX %s\n", i, &path[0], path.c_str());
        }
	});
}
