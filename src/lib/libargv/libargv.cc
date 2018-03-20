#include <libc/component.h>
#include <base/exception.h>
#include <base/log.h>
#include <base/attached_rom_dataspace.h>

#include <stdio.h>
#include <stdlib.h>

extern "C"
int main (int argc, char **argv);

Genode::Env *genode_env;

template <size_t CAPACITY, int MAXARGS>
class Arguments
{
    public:
        class Out_of_memory       : public Genode::Exception { };
        class Too_many_arguments  : public Genode::Exception { };
        class Args_already_frozen : public Genode::Exception { };

    private:
        char    *_argv[MAXARGS];
        char    _buffer[CAPACITY];
        size_t  _offset = 0;
        int     _argc = 0;
        bool    _is_terminated = false;

        char * _alloc(size_t size)
        {
            if (_is_terminated) throw Args_already_frozen();
            if (_argc >= MAXARGS) throw Too_many_arguments();
            if (_offset + size >= CAPACITY) throw Out_of_memory();

            _argv[_argc] = &_buffer[_offset];
            char *result = _argv[_argc];
            _offset += size + 1;
            return result;
        }

        void _terminate(void)
        {
            _argv[_argc] = nullptr;
            _is_terminated = true;
        }

    public:

        Arguments() { };

        char * alloc(size_t size)
        {
            char *result = _alloc(size);
            _argc++;
            return result;
        }

        char ** argv()
        {
            if (!_is_terminated) _terminate();
            return _argv;
        }

        int argc()
        {
            if (!_is_terminated) _terminate();
            return _argc;
        }

};

void Libc::Component::construct(Libc::Env &env)
{
    using namespace Genode;

    genode_env = &env;
    Arguments<4096,64> _arguments;

    Genode::Attached_rom_dataspace config { env, "config" };
    Genode::Xml_node config_xml = config.xml();

    try
    {
        Xml_node arglist = config_xml.sub_node("argv");
        Xml_attribute progname = arglist.attribute("progname");

        char *next = _arguments.alloc(progname.value_size());
        progname.value(next, progname.value_size() + 1);

        try
        {
            Genode::Xml_node arg = arglist.sub_node("arg");

            for(;;)
            {
                Xml_attribute value = arg.attribute("value");
                char *next = _arguments.alloc(value.value_size());
                value.value(next, value.value_size() + 1);
                if (arg.last("arg")) break;
                arg = arg.next("arg");
            }
        }
        catch (Xml_node::Nonexistent_attribute)
        {
            error("No 'value' attribute in argument");
            return;
        }
        catch (Xml_node::Nonexistent_sub_node)
        {
            error("No 'arg' present");
            return;
        }
    }
    catch (Xml_node::Nonexistent_attribute)
    {
        error("No 'progname' attribute in argv");
        return;
    }
    catch (Xml_node::Nonexistent_sub_node)
    {
        // argv is not required
        log("No argv configured");
    }

    Libc::with_libc([&] {
        setprogname (_arguments.argv()[0]);
        exit(main(_arguments.argc(), _arguments.argv()));
    });
}
