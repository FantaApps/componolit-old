ANDROID_PORT = lzma
ANDROID_DIR = liblzma/C
ANDROID_SECTIONS = /cc_library[@name=liblzma]

include $(call select_from_repositories,lib/mk/android-lib.inc)
