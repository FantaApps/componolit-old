# For netinet/icmp6.h
INC_DIR += $(call select_from_ports,libc)/src/lib/libc/sys

SRC_CC = \
	dalvik/src/main/native/org_apache_harmony_dalvik_NativeTestTarget.cpp \
	luni/src/main/native/java_lang_invoke_MethodHandle.cpp \
	luni/src/main/native/libcore_icu_TimeZoneNames.cpp \
	luni/src/main/native/java_lang_StringToReal.cpp \
	luni/src/main/native/ExecStrings.cpp \
	luni/src/main/native/java_util_regex_Matcher.cpp \
	luni/src/main/native/cbigint.cpp \
	luni/src/main/native/IcuUtilities.cpp \
	luni/src/main/native/libcore_icu_NativeConverter.cpp \
	luni/src/main/native/android_system_OsConstants.cpp \
	luni/src/main/native/libcore_icu_ICU.cpp \
	luni/src/main/native/libcore_io_Memory.cpp \
	luni/src/main/native/libcore_io_Linux.cpp \
	luni/src/main/native/sun_misc_Unsafe.cpp \
	luni/src/main/native/libcore_util_NativeAllocationRegistry.cpp \
	luni/src/main/native/Register.cpp \
	luni/src/main/native/java_util_regex_Pattern.cpp \
	luni/src/main/native/libcore_io_AsynchronousCloseMonitor.cpp \
	luni/src/main/native/JniException.cpp \
	luni/src/main/native/java_math_NativeBN.cpp \
	luni/src/main/native/valueOf.cpp \
	luni/src/main/native/NetworkUtilities.cpp \
	luni/src/main/native/org_apache_harmony_xml_ExpatParser.cpp \
	luni/src/main/native/ZipUtilities.cpp \

CC_OPT += -D__GENODE__
CC_OPT += -Wno-error=maybe-uninitialized

LIBS += expat libicuuc libicui18n zlib libnativehelper boringssl libc stdcxx liblog libbase pthread

include $(call select_from_repositories,lib/import/import-libjavacore.mk)

SHARED_LIB = yes
CC_CXX_WARN_STRICT =

