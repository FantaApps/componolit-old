#include <libexec.h>
#include <util/string.h>
#include <timer_session/connection.h>

using namespace Genode;

int Componolit::Libexec::_current_exec_count()
{
    return _exec_count++;
}

int Componolit::Libexec::Exec (const char *binary, const char *arguments[], const char **environ)
{
    typedef String<64> Name;
    bool exists = false;
    bool exited = false;
    int code    = -1;
    int delay_ms = 500;

    enum { MAX_ARG_LEN = 48 };
    char app[MAX_ARG_LEN];

    String<10> ram = "1M";
    String<10> caps = "100";
    bool verbose = false;

    Timer::Connection _timer(_env);

    _config.update();

    try {
        Xml_node libexec_config = _config.xml().sub_node("libexec");
        ram = libexec_config.attribute_value("ram", ram);
        caps = libexec_config.attribute_value("caps", caps);
        verbose = libexec_config.attribute_value("verbose", false);
    }
    catch (Xml_node::Nonexistent_sub_node) { }

    if (verbose)
    {
        log("Starting ", Genode::Cstring(binary), " with ram=", ram, " caps=", caps);
    }

    _init_config.generate([&] (Xml_generator &xml)
    {
        xml.node("report", [&] () { xml.attribute("delay_ms", delay_ms); });

        xml.node("parent-provides", [&] ()
        {
            xml.node("service", [&] () { xml.attribute("name", "CAP"); });
            xml.node("service", [&] () { xml.attribute("name", "CPU"); });
            xml.node("service", [&] () { xml.attribute("name", "LOG"); });
            xml.node("service", [&] () { xml.attribute("name", "PD"); });
            xml.node("service", [&] () { xml.attribute("name", "ROM"); });
            xml.node("service", [&] () { xml.attribute("name", "File_system"); });
            xml.node("service", [&] () { xml.attribute("name", "Timer"); });
            xml.node("service", [&] () { xml.attribute("name", "Rtc"); });
            xml.node("service", [&] () { xml.attribute("name", "Report"); });
        });
    
        xml.node("start", [&] ()
        {
            snprintf(app, sizeof(app), "%s(%d)", binary, _current_exec_count());
            xml.attribute("name", app);
    
            xml.node("binary", [&] () { xml.attribute("name", binary); });

            xml.attribute("caps", caps);
    
            xml.node("resource", [&] ()
            {
                xml.attribute("name", "RAM");
                xml.attribute("quantum", ram);
            });
            xml.node("config", [&] ()
            {
                xml.node("argv", [&] ()
                {
                    xml.attribute("progname", binary);
                    for (int i = 0; arguments[i]; i++)
                    {
                        xml.node("arg", [&] () { xml.attribute("value", arguments[i]); });
                    };
                });
    
                if (environ) {
                    xml.node("environ", [&] ()
                    {
                        for (const char **env = environ; env && *env != 0; env++)
                        {
                            char *key;
                            char entry[4096];
                            strncpy (entry, *env, sizeof (entry));

                            for (key = entry; key && *key != '='; key++);
                            if (!key) break;

                            *key++ = '\0';
                            xml.node("env", [&] () {
                                xml.attribute("name", entry);
                                xml.attribute("value", key);
                            });
                        };
                    });
                }
    
                xml.node("vfs", [&] ()
                {
                    xml.node("dir", [&] ()
                    {
                        xml.attribute("name", "dev");
                        xml.node("log", [&] () { });
                        xml.node("rtc", [&] () { });
                        xml.node("null", [&] () { });
                    });

                    xml.node("fs", [&] () { });
                });
                xml.node("libc", [&] ()
                {
                    xml.attribute("stdout", "/dev/log");
                    xml.attribute("stderr", "/dev/log");
                    xml.attribute("rtc", "/dev/rtc");
                });
            });
    
            xml.node("route", [&] ()
            {
                xml.node("any-service", [&] ()
                {
                    xml.node("parent", [&] () { });
                });
            });
        });
    });

    // Retrieve exit state
    for (;;)
    {
        _init_state.update();
        _init_state.xml().for_each_sub_node("child", [&] (Xml_node child) {
            if (child.attribute_value("name", Name()) == app) {
                exists = true;
                if (child.has_attribute("exited")) {
                    exited = true;
                    code = child.attribute_value("exited", 0L);
                }
            }
        });

        if (exists and exited)
        {
            if (verbose) log("Exiting with code ", code);
            return code;
        }
        _timer.msleep(delay_ms/2);
    };
};
