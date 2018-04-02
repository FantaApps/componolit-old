ANDROID_PORT = libart
ANDROID_DIR = art
ANDROID_SOURCES = compiler
ANDROID_INCLUDES = compiler compiler/driver dexlayout disassembler
ANDROID_BUILDFILES = test/Android.bp build/Android.bp compiler/Android.bp

ANDROID_SECTIONS = \
	/art_cc_library[@name=libart-compiler] \
	/art_cc_library[@name=libart-compiler]/codegen/arm \
	/art_cc_library[@name=libart-compiler]/codegen/arm64 \
	/art_cc_library[@name=libart-compiler]/codegen/mips \
	/art_cc_library[@name=libart-compiler]/codegen/mips64 \
	/art_cc_library[@name=libart-compiler]/codegen/x86 \
	/art_cc_library[@name=libart-compiler]/codegen/x86_64 \
	/gensrcs[@name=art_compiler_operator_srcs]

include $(call select_from_repositories,lib/mk/libart-defaults.inc)
include $(call select_from_repositories,lib/mk/android-lib.inc)
include $(call select_from_repositories,lib/import/import-libart-compiler.mk)

INC_DIR += $(call select_from_ports,libart)/art/compiler

BASEDIR = $(call select_from_ports,libart)/art/compiler
GENTOOL = $(BASEDIR)/$($(ANDROID_NAME)_TOOL_FILES)
HEADERS = $(addprefix $(BASEDIR)/,$(filter %.h,$($(ANDROID_NAME)_SRCS)))
OUTPUT  = $($(ANDROID_NAME)_OUTPUT_EXTENSION)
GENDIR  = $(LIB_CACHE_DIR)/$(ANDROID_BUILDTYPE)/$(ANDROID_NAME)

$(GENDIR)/$(OUTPUT): $(HEADERS)
	$(VERBOSE)$(GENTOOL) $(BASEDIR) $(HEADERS) > $@.tmp
	$(VERBOSE)mv $@.tmp $@

vpath % $(GENDIR)
SRC_C += $(OUTPUT)

# dexlayout includes jni.h which is provided by libnativehelper. As it
# is not a dependency in Android.bp, we need to add it manually.
LIBS += libnativehelper

LIBS += lzma libssl libcutils libutils vixl

# FIXME: SUPPRESS WARNINGS! DEVELOPMENT ONLY - REMOVE FOR PRODUCTION!
$(warning SUPPRESSING WARNINGS - REMOVE FOR PRODUCTION!)
CC_OPT += -w

CC_CXX_WARN_STRICT =
