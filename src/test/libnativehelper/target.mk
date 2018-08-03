TARGET = libnativehelper_test

ANDROID_PORT	 = libnativehelper
ANDROID_DIR		 = libnativehelper/tests
ANDROID_SECTIONS = /cc_test[@name=JniInvocation_test]

include $(call select_from_repositories,lib/mk/android-prg.inc)

SRC_CC += main.cc
LIBS   += gtest libargv
