TARGET = dexlayout

ANDROID_PORT = libart
ANDROID_DIR = art
ANDROID_SOURCES = dexlayout
ANDROID_BUILDFILES = Android.bp test/Android.bp build/Android.bp dexlayout/Android.bp
ANDROID_SECTIONS = /art_cc_binary[@name=dexlayout]

include $(call select_from_repositories,lib/mk/libart-defaults.inc)
include $(call select_from_repositories,lib/mk/android-prg.inc)

LIBS += libnativehelper libart-dexlayout libargv librwall
