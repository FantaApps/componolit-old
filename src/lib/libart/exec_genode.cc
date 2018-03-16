// libc includes
#include <dlfcn.h>
#include <getopt.h>

// std includes
#include <string>
#include <functional>

// Genode includes
#include <base/log.h>
#include <util/string.h>

// libart includes
#include <exec_utils.h>

// Componolit includes
#include <libexec.h>

extern Genode::Env *genode_env;

bool art::Exec(std::vector<std::string>& arg_vector, std::string* error_msg)
{
    // Get binary (base)name and append libary extension
    std::string binary = arg_vector[0].substr(arg_vector[0].find_last_of('/') + 1);

    std::vector<char *> argv;
    for (size_t i = 1; i < arg_vector.size(); ++i)
    {
        char *argument = const_cast<char *>(arg_vector[i].c_str());
        argv.push_back(argument);
    }
    argv.push_back(nullptr);

    Componolit::Libexec _le(*genode_env);
    return _le.Exec((const char *)binary.c_str(), (const char **)&argv[0]);
};
