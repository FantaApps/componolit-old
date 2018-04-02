# Filter out GCC 7 options unsupported by GCC 6.3
ANDROID_EXCLUDE_OPT += \
	-Wimplicit-fallthrough \
	-Wint-to-void-pointer-cast \
	-Wthread-safety \
	-Wthread-safety-negative \
	-Wunreachable-code-break \
	-Wunreachable-code-return \
	-Wused-but-marked-unused \
	-Wno-undefined-var-template \
	-Wno-constant-conversion \
	-Wredundant-decls \
	-Wno-frame-larger-than=

# Use sources from runtime
ANDROID_SOURCES += runtime

# include runtime and runtime/arch
ANDROID_INCLUDES += runtime runtime/arch

# Filter out known warnings that cause trouble with our toolchain
# -Wshadow:
#	Prevent errors regarding hidden constructor for struct
# 	sigaction/sigaltstack/sigstack, sigvec and others
ANDROID_EXCLUDE_OPT += \
	-Wshadow

# In case we use this without including android.inc
CC_OPT += -D__GENODE__

# Taken from build/art.go
CC_OPT += -DIMT_SIZE=43
CC_OPT += -DART_DEFAULT_GC_TYPE_IS_SS
CC_OPT += -DART_FRAME_SIZE_LIMIT=1736
CC_OPT += -DART_ENABLE_VDEX
CC_OPT += -DART_BASE_ADDRESS_MIN_DELTA=-0x1000000
CC_OPT += -DART_BASE_ADDRESS_MAX_DELTA=0x1000000
CC_OPT += -DART_STACK_OVERFLOW_GAP_arm=8192
CC_OPT += -DART_STACK_OVERFLOW_GAP_arm64=8192
CC_OPT += -DART_STACK_OVERFLOW_GAP_mips=16384
CC_OPT += -DART_STACK_OVERFLOW_GAP_mips64=16384
CC_OPT += -DART_STACK_OVERFLOW_GAP_x86=8192
CC_OPT += -DART_STACK_OVERFLOW_GAP_x86_64=8192

# Taken from build/soong/android/config.go, Mips/Mips64 would be 0x5C000000
CC_OPT += -DART_BASE_ADDRESS=0x70000000

# FIXME: The _Atomic keyword is not available in the Genode toolchain
CC_OPT += -D_Atomic=

# FIXME: _Bool is not available
CC_OPT += -D_Bool=bool

# FIXME: __auto_type is not available
CC_OPT += -D__auto_type=auto

# O_CLOEXEC does not exist in FreeBSD libc
CC_OPT += -DO_CLOEXEC=0

# MAP_32BIT does not exist in FreeBSD libc
CC_OPT += -DMAP_32BIT=0

# pthread_getname_np does not exist on Genode.
CC_OPT += -D'pthread_getname_np(self,name,len)=(-1)'

CC_OPT += -I$(call select_from_repositories,src/lib/libart/include)

# Include path for generated asm_support_gen.h
# We don't generate it as it comes with the sources.
CC_OPT += -I$(call select_from_ports,libart)/art/runtime/generated

# Enable UINTPTR_MAX
CC_OPT += -D__STDC_LIMIT_MACROS=1

# Enable UINT64_C/INT64_C etc. in stdint.h
CC_OPT += -D__STDC_CONSTANT_MACROS=1

LIBS += pthread

# Add libart-defaults.inc to list of Android makefiles to rebuild android.mk when it changes
ANDROID_MK += $(call select_from_repositories,lib/mk/libart-defaults.inc)

LIBS += valgrind dlmalloc zlib icu cmdline libziparchive pthread librwall
