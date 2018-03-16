ANDROID_NAME = $(TARGET)
ANDROID_BUILDTYPE = prg

# Add android build fragments to rebuild android.mk when build files change
ANDROID_MK += $(call select_from_repositories,lib/mk/android-lib.inc)
ANDROID_MK += $(call select_from_repositories,lib/mk/android.inc)

include $(call select_from_repositories,lib/mk/android.inc)

LIBS += libargv
