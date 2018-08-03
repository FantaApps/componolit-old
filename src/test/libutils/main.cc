#include <stdlib.h> /* 'exit'   */
#include <gtest/gtest.h>

extern "C" int main(int argc, char **argv)
{
		testing::InitGoogleTest(&argc, argv);
		exit(RUN_ALL_TESTS());
};
