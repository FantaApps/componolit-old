ANDROID_PORT = libart
ANDROID_DIR = art
ANDROID_SOURCES = dexlayout
ANDROID_BUILDFILES = test/Android.bp build/Android.bp dexlayout/Android.bp

ANDROID_SECTIONS = \
	/art_cc_library[@name=libart-dexlayout] \

include $(call select_from_repositories,lib/mk/libart-defaults.inc)
include $(call select_from_repositories,lib/mk/android-lib.inc)

# dexlayout includes jni.h which is provided by libnativehelper. As it
# is not a dependency in Android.bp, we need to add it manually.
LIBS += libnativehelper
