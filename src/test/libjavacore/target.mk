TARGET = libjavacore_test

vpath %.cpp $(call select_from_ports,libcore)/luni/src/test/native

SRC_CC = \
    main.cc \
    libcore_dalvik_system_JniTest.cpp \
    libcore_java_io_FileTest.cpp \
    libcore_java_lang_ThreadTest.cpp \
    libcore_java_nio_BufferTest.cpp \
    libcore_libcore_util_NativeAllocationRegistryTest.cpp

LIBS += gtest libargv libjavacore libbacktrace posix

# Add -fno-builtin so that the compiler doesn't attempt to inline
# memcpy calls that are not really aligned.
OPT_CC += -fno-builtin
