#include <base/log.h>
#include <stdlib.h>
#include <gtest/gtest.h>

extern "C" int main(int argc, char **argv)
{
		testing::InitGoogleTest(&argc, argv);
		int rv = chdir("/tmp");
		if (rv < 0) {
			Genode::log ("Error changing to /tmp");
			exit (1);
		}
		exit(RUN_ALL_TESTS());
};
