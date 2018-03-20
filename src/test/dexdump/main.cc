/* Genode includes */
#include <libc/component.h>

/* libc includes */
#include <stdlib.h> /* 'exit'   */

#include <gtest/gtest.h>

int
main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);
	exit (RUN_ALL_TESTS());
}
