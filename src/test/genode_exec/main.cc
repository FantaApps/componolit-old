#include <base/log.h>
#include <libc/component.h>
#include <exec_utils.h>
#include <fstream>

int main(int argc, char **argv)
{
        bool rv;
        std::vector<std::string> arguments;
        std::string error_msg;

        arguments.push_back("/path/does/not/matter/write");
        arguments.push_back("/tmp/testfile.123");
        arguments.push_back("SOME CONTENT");

        // Execute library main of library called 'write'
        rv = art::Exec(arguments, &error_msg);
        if (!rv)
        {
            Genode::error("Error running write");
            exit(1);
        }

        // Check for file '/tmp/testfile.123' with content 'SOME CONTENT'
        std::string compare;
        std::ifstream file(arguments[1]);

        if (! file.is_open())
        {
            Genode::error("File not open");
            exit(1);
        }

        getline(file, compare);
        if (compare != arguments[2])
        {
            Genode::error("File content differs: is=>", compare.c_str(), "< should=>", arguments[2].c_str(), "<");
            exit(2);
        }

        std::vector<std::string> arguments2;

        arguments2.push_back("write");
        arguments2.push_back("/tmp/nonexistent/testfile.123");
        arguments2.push_back("SOME CONTENT");

        // Execute library main of library called 'write'
        rv = art::Exec(arguments2, &error_msg);
        if (rv)
        {
            Genode::error("Error detecting non-existent path");
            exit(1);
        }

        exit(0);
}
