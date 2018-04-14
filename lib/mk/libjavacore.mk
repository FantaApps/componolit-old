LIBJAVACORE_DIR = $(call select_from_ports,libcore)/libcore

vpath %.cpp $(LIBJAVACORE_DIR)/luni/src/main/native $(LIBJAVACORE_DIR)/dalvik/src/main/native

LIBCORE_DIR = $(call select_from_repositories,src/lib/libcore)
LIBCORE_INC = $(call select_from_ports,libcore)/libcore/include
INC_DIR += $(LIBCORE_DIR) $(LIBCORE_INC)

# For netinet/icmp6.h
INC_DIR += $(call select_from_ports,libc)/src/lib/libc/sys

SRC_CC = \
	org_apache_harmony_dalvik_NativeTestTarget.cpp \
	android_system_OsConstants.cpp \
	cbigint.cpp \
	ExecStrings.cpp \
	IcuUtilities.cpp \
	java_lang_invoke_MethodHandle.cpp \
	java_lang_StringToReal.cpp \
	java_math_NativeBN.cpp \
	java_util_regex_Matcher.cpp \
	java_util_regex_Pattern.cpp \
	JniException.cpp \
	libcore_icu_ICU.cpp \
	libcore_icu_NativeConverter.cpp \
	libcore_icu_TimeZoneNames.cpp \
	libcore_io_AsynchronousCloseMonitor.cpp \
	libcore_io_Memory.cpp \
	libcore_util_NativeAllocationRegistry.cpp \
	NetworkUtilities.cpp \
	org_apache_harmony_xml_ExpatParser.cpp \
	Register.cpp \
	sun_misc_Unsafe.cpp \
	valueOf.cpp \
	ZipUtilities.cpp

CC_OPT += -D__GENODE__
LIBS += expat libicuuc libicui18n zlib libnativehelper boringssl libc stdcxx liblog libbase

include $(call select_from_repositories,lib/import/import-libjavacore.mk)

SHARED_LIB = yes
CC_CXX_WARN_STRICT =
