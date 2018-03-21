ANDROID_LIB := libziparchive
include $(call select_from_repositories,lib/import/import-android.inc)

# UINT16_MAX not available
CC_OPT += -DUINT16_MAX=0xffff
