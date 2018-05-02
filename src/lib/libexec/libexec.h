#ifndef _INCLUDE_LIBEXEC_H_
#define _INCLUDE_LIBEXEC_H_

#include <base/component.h>
#include <base/attached_rom_dataspace.h>
#include <util/list.h>
#include <util/string.h>
#include <os/reporter.h>

namespace Componolit {

    using namespace Genode;

    typedef Genode::String<64> Argument;

    class Libexec {

        private:
            Genode::Env &_env;
            Genode::Expanding_reporter _init_config;
            Genode::Attached_rom_dataspace _config;
            Genode::Attached_rom_dataspace _init_state;
            unsigned int _exec_count = 0;

            void _handle_init_state();
            int _current_exec_count();

        public:

            Libexec(Genode::Env &env)
            : _env(env)
            , _init_config(env, "config", "init_config")
            , _config(env, "config")
            , _init_state(env, "init_state") { };

            int Exec (const char *app, const char *arguments[], const char **environ = nullptr);
    };
}

#endif // _INCLUDE_LIBEXEC_H_
