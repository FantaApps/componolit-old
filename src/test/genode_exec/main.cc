#include <base/log.h>
#include <libc/component.h>
#include <exec_utils.h>
#include <fstream>

void Libc::Component::construct(Libc::Env &env)
{
	Libc::with_libc([&] {

        std::vector<std::string> arguments;
        std::string error_msg;

        arguments.push_back("/path/does/not/matter/write");
        arguments.push_back("/tmp/testfile.123");
        arguments.push_back("SOME CONTENT");

        // Execute library main of library called 'write'
        art::Exec(arguments, &error_msg);

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

        exit(0);
	});
}
