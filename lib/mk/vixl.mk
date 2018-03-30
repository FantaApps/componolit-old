ANDROID_PORT = vixl
ANDROID_DIR = vixl
ANDROID_INCLUDES = src
ANDROID_SECTIONS = /cc_library[@name=libvixl-arm64]

include $(call select_from_repositories,lib/mk/android-lib.inc)
include $(call select_from_repositories,lib/import/import-vixl.mk)

SRC_CC = \
	src/aarch64/assembler-aarch64.cc \
	src/aarch64/disasm-aarch64.cc \
	src/aarch64/macro-assembler-aarch64.cc \
	src/compiler-intrinsics-vixl.cc \
	src/aarch64/cpu-aarch64.cc \
	src/aarch64/instructions-aarch64.cc \
	src/aarch64/operands-aarch64.cc \
	src/utils-vixl.cc \
	src/aarch64/debugger-aarch64.cc \
	src/aarch64/instrument-aarch64.cc \
	src/aarch64/simulator-aarch64.cc \
	src/aarch64/decoder-aarch64.cc \
	src/aarch64/logic-aarch64.cc \
	src/code-buffer-vixl.cc

CC_OPT += -DVIXL_INCLUDE_SIMULATOR_AARCH64
CC_OPT += -DVIXL_CODE_BUFFER_MMAP
CC_OPT += -DVIXL_INCLUDE_TARGET_A64
