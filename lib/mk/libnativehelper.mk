ANDROID_PORT     = libnativehelper
ANDROID_DIR      = libnativehelper
ANDROID_SECTIONS += /cc_library[@name=libnativehelper]
ANDROID_SECTIONS += /cc_library_headers[@name=jni_headers]
ANDROID_INCLUDES = include/nativehelper

vpath %.cc $(call select_from_repositories,src/lib/libnativehelper)
SRC_CC += DummyAsynchronousCloseMonitor.cpp

include $(call select_from_repositories,lib/mk/android-lib.inc)

LIBS += libcore_includes
