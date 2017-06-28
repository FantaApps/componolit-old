ANDROID_PORT       = liblog
ANDROID_DIR        = system/core/liblog
ANDROID_INCLUDES   = ../include
ANDROID_SECTIONS   = /cc_library[@name=liblog] /cc_library[@name=liblog]/target/host

include $(call select_from_repositories,lib/mk/android-lib.inc)

CC_OPT += -Wno-unused-variable -Wno-unused-function
