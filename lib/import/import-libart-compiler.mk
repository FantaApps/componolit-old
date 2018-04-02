ANDROID_LIB := libart-compiler
include $(call select_from_repositories,lib/import/import-android.inc)

# Dummy defines for MIPS ELF attributes which Genodes elf.h does not defined
CC_OPT += -DPT_MIPS_ABIFLAGS=0 -DSHT_MIPS_ABIFLAGS=0

CC_OPT += -DART_ENABLE_CODEGEN_arm=1
CC_OPT += -DART_ENABLE_CODEGEN_arm64=1
CC_OPT += -DART_ENABLE_CODEGEN_x86=1
CC_OPT += -DART_ENABLE_CODEGEN_x86_64=1
CC_OPT += -DART_ENABLE_CODEGEN_mips=1
CC_OPT += -DART_ENABLE_CODEGEN_mips64=1
