TARGET = libjavacore_test

SRC_CC = \
	main.cc \
	luni/src/test/native/dalvik_system_JniTest.cpp \
	luni/src/test/native/libcore_java_lang_ThreadTest.cpp \
	luni/src/test/native/libcore_util_NativeAllocationRegistryTest.cpp \
	luni/src/test/native/libcore_java_nio_BufferTest.cpp \
	luni/src/test/native/libcore_java_io_FileTest.cpp \
	luni/src/test/native/libcore_io_Memory_test.cpp

LIBS += gtest libargv libjavacore libbacktrace posix stdcxx libnativehelper

# Add -fno-builtin so that the compiler doesn't attempt to inline
# memcpy calls that are not really aligned.
CC_OPT += -fno-builtin
CC_OPT += -D__GENODE__
CC_CXX_WARN_STRICT =
