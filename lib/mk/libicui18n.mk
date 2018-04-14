ANDROID_PORT = android-icu
ANDROID_DIR = icu/icu4c/source
ANDROID_SOURCES = i18n
ANDROID_INCLUDES = i18n
ANDROID_BUILDFILES = Android.bp i18n/Android.bp

ANDROID_SECTIONS += /cc_library_shared[@name=libicui18n]

include $(call select_from_repositories,lib/import/import-libicui18n.mk)
include $(call select_from_repositories,lib/mk/android-lib.inc)

LIBS += libicuuc

CC_OPT += -Wno-error=unused-but-set-variable
CC_OPT += -Wno-error=maybe-uninitialized
CC_OPT += -Wno-error=misleading-indentation
CC_OPT += -Wno-error=deprecated-declarations
