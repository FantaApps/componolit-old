/* libc includes */
#include <stdlib.h> /* 'exit'   */

#include <gtest/gtest.h>

/* provided by the application */
extern "C" int main(int argc, char const **argv)
{
	testing::InitGoogleTest(&argc, argv);
	exit(RUN_ALL_TESTS());
};
