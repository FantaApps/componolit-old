ANDROID_PORT	 = core
ANDROID_DIR  	     = system/core/libziparchive
ANDROID_EXCLUDE_LIBS = libz
ANDROID_SECTIONS     = /cc_library[@name=libziparchive] /cc_library[@name=libziparchive]/target/host

include $(call select_from_repositories,lib/mk/android-lib.inc)

LIBZIPARCHIVE_DIR = $(call select_from_repositories,src/lib/libziparchive)
vpath %.cc $(LIBZIPARCHIVE_DIR)
INC_DIR += $(LIBZIPARCHIVE_DIR)

# Use local implementations of lseek64/pread64
CC_OPT += -include ops64.h
SRC_CC += ops64.cc

LIBS += zlib
CC_OPT += -Wno-error=unused-variable
