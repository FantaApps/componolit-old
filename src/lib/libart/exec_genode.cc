// libc includes
#include <dlfcn.h>

// std includes
#include <string>
#include <functional>

// Genode includes
#include <base/log.h>
#include <util/string.h>

// libart includes
#include <exec_utils.h>

bool art::Exec(std::vector<std::string>& arg_vector, std::string* error_msg)
{
    // Get binary (base)name and append libary extension
    std::string binary = arg_vector[0].substr(arg_vector[0].find_last_of('/') + 1);
    binary.append(".lib.so");

    void *handle = dlopen(binary.c_str(), RTLD_GLOBAL);
    if (handle == nullptr)
    {
        Genode::error("Error dlopen()ing '", binary.c_str(), "'");
        return false;
    }

    typedef int (* main_t)(int, char **);
    main_t main = (main_t)dlsym(handle, "main");
    if (main == nullptr)
    {
        Genode::error("Error getting main(): ", Genode::Cstring(dlerror()));
        dlclose(handle);
        return false;
    }

    std::vector<char *> argv;
    for (size_t i = 0; i < arg_vector.size(); ++i)
    {
        char *argument = const_cast<char *>(arg_vector[i].c_str());
        argv.push_back(argument);
    }
    argv.push_back(nullptr);

    return (main(argv.size() - 1, &argv[0]) == 0);
};
