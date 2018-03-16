// Genode includes
#include <base/log.h>
#include <base/component.h>
#include <base/heap.h>
#include <os/reporter.h>

// Componolit includes
#include <libexec.h>

namespace Libexec_test {
    struct Main;
}

using namespace Genode;
using namespace Componolit;


struct Libexec_test::Main {

    Env &_env;
    Libexec _le;

    Main(Env &env) : _env(env), _le(env)
    {
        bool fail = false;

        const char *arguments1[] = {"/tmp/test", "This value", 0};
        if (_le.Exec("write", arguments1) != 0)
        {
            log("Test #1 failed");
            fail = true;
        }

        const char *arguments2[] = {"/tmp/does/not/exist/test", "This value ", 0};
        if (_le.Exec("write", arguments2) == 0)
        {
            log("Test #2 failed");
            fail = true;
        }

        if (!fail) log ("Done.");
        
    }
};

void Component::construct(Genode::Env &env)
{
    env.exec_static_constructors();
    static Libexec_test::Main main(env);
}
