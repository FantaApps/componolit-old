ANDROID_PORT = android-icu
ANDROID_DIR = icu/icu4c/source
ANDROID_SOURCES = common
ANDROID_INCLUDES = common
ANDROID_BUILDFILES = Android.bp common/Android.bp

ANDROID_SECTIONS += /cc_library_shared[@name=libicuuc]
ANDROID_EXCLUDE_LIBS = libicuuc_stubdata

include $(call select_from_repositories,lib/import/import-libicuuc.mk)
include $(call select_from_repositories,lib/mk/android-lib.inc)

CC_OPT += -Wno-error=unused-but-set-variable
CC_OPT += -Wno-error=maybe-uninitialized
