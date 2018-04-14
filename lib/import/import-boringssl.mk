ANDROID_LIB := boringssl
ANDROID_EXCLUDE_OPT = -fvisibility=hidden

include $(call select_from_repositories,lib/import/import-android.inc)

