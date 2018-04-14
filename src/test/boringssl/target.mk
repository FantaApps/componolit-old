TARGET = boringssl_crypto_test

ANDROID_PORT	   = boringssl
ANDROID_DIR		   = boringssl
ANDROID_INCLUDES   = . include
ANDROID_BUILDFILES = Android.bp sources.bp
ANDROID_EXCLUDE_LIBS = libcrypto posix

ANDROID_SECTIONS += /cc_test[@name=boringssl_crypto_test]

SRC_CC += \
	src/crypto/test/file_test.cc \
	src/crypto/test/malloc.cc \
	src/crypto/test/test_util.cc

LIBS += boringssl gtest

include $(call select_from_repositories,lib/mk/android-prg.inc)
