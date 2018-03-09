/* Genode includes */
#include <libc/component.h>

/* libc includes */
#include <stdlib.h> /* 'exit'   */

#include <base/logging.h>
#include <gtest/gtest.h>

extern int    genode_argc;
extern const char **genode_argv;

/* provided by the application */
extern "C" int main(int argc, char const **argv);

void Libc::Component::construct(Libc::Env &env)
{
	Libc::with_libc([&] {

		char const *argv[] = {
			"/bin/test_art_runtime",
			"--gtest_filter=-None",
			0
		};

		genode_argc = 2;
		genode_argv = argv;
		setprogname (genode_argv[0]);

		android::base::InitLogging((char **)genode_argv, android::base::StderrLogger, android::base::DefaultAborter);
		exit(main(genode_argc, genode_argv));
	});
}
