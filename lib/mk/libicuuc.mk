ANDROID_PORT = android-icu
ANDROID_DIR = icu/icu4c/source
ANDROID_SOURCES = common stubdata
ANDROID_INCLUDES = common
ANDROID_BUILDFILES = Android.bp common/Android.bp

ANDROID_SECTIONS += /cc_library_shared[@name=libicuuc]
ANDROID_EXCLUDE_LIBS = libicuuc_stubdata

include $(call select_from_repositories,lib/import/import-libicuuc.mk)
include $(call select_from_repositories,lib/mk/android-lib.inc)

CC_OPT += -Wno-error=unused-but-set-variable
CC_OPT += -Wno-error=maybe-uninitialized

# Generate icudt58_dat symbol from stub data
# Taken from Genode's libports/lib/mk/icu.mk
ICU_DAT             = icudt58l.dat
ICU_DAT_SYMBOL_NAME = icudt58_dat
SRC_BIN += $(ICU_DAT)

binary_$(ICU_DAT).o : $(ICU_DAT)
	$(MSG_CONVERT)$@
	$(VERBOSE)echo ".global $(ICU_DAT_SYMBOL_NAME); .section .rodata; .align 4; $(ICU_DAT_SYMBOL_NAME):; .incbin \"$<\"" |\
	          $(AS) $(AS_OPT) -f -o $@ -
