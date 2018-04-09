ANDROID_LIB := vixl
include $(call select_from_repositories,lib/import/import-android.inc)

# Enable UINT64_C/INT64_C etc. in stdint.h
CC_OPT += -D__STDC_CONSTANT_MACROS

# Enable PTRDIFF_MAX etc. in stdint.h
CC_OPT += -D__STDC_LIMIT_MACROS

ifneq ($(VIXL_DEBUG),)
CC_OPT += -DVIXL_DEBUG=1
endif
