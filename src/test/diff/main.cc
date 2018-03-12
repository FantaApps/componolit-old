#include <base/log.h>
#include <libc/component.h>
#include <exec_utils.h>
#include <iostream>
#include <fstream>

static void write_file (std::string filename, std::string &content)
{
    std::ofstream file;
    file.open (filename);
    file << content;
    file.close();
}

void Libc::Component::construct(Libc::Env &env)
{
	Libc::with_libc([&] {

        std::string error_msg;

        std::string content1 = "THIS IS A\nFILE WITH\nSOME CONTENT\n";
        std::string content2 = "THIS IS ANOTHER\nFILE WITH DIFFERENT\nCONTENT\n";

        write_file("/tmp/testfile1", content1);
        write_file("/tmp/testfile2", content1);
        write_file("/tmp/testfile3", content2);

        // Identical content
        std::vector<std::string> same_content_args =
            { "/path/does/not/matter/diff",
              "/tmp/testfile1",
              "/tmp/testfile2" };

        bool result = art::Exec(same_content_args, &error_msg);
        if (!result) exit(1);

        // Different content
        std::vector<std::string> different_content_args =
            { "/path/does/not/matter/diff",
              "/tmp/testfile2",
              "/tmp/testfile3" };

        result = art::Exec(different_content_args, &error_msg);
        if (result) exit(1);

        // Identical file
        std::vector<std::string> identical_file_args =
            { "/path/does/not/matter/diff",
              "/tmp/testfile1",
              "/tmp/testfile1" };

        result = art::Exec(identical_file_args, &error_msg);
        if (!result) exit(1);

        // Exit with 42 so we can distinguish unwanted exits of diff from
        // successful exists of the test case.
        exit(42);
	});
}
