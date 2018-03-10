ANDROID_PORT = libart
ANDROID_DIR = art
ANDROID_SOURCES = sigchainlib
ANDROID_BUILDFILES = build/Android.bp sigchainlib/Android.bp
ANDROID_SECTIONS = /cc_library[@name=libsigchain]

include $(call select_from_repositories,lib/mk/libart-defaults.inc)
include $(call select_from_repositories,lib/mk/android-lib.inc)

vpath %.cc $(call select_from_repositories,src/lib/sigchainlib)
SRC_CC += sigchainlib_genode.cc

LIBS += liblog
