ANDROID_PORT = boringssl
ANDROID_DIR = boringssl
ANDROID_BUILDFILES = Android.bp sources.bp

ANDROID_SECTIONS += /cc_library[@name=libcrypto]
ANDROID_SECTIONS += /cc_library[@name=libcrypto]/target/android_$(ANDROID_ARCH)

include $(call select_from_repositories,lib/import/import-boringssl.inc)
include $(call select_from_repositories,lib/mk/android-lib.inc)

LIBS += pthread
