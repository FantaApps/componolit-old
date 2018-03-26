TARGET = libziparchive_test

ANDROID_PORT	 = core
ANDROID_DIR		 = system/core/libziparchive
ANDROID_EXCLUDE_LIBS = libz
ANDROID_SECTIONS = /cc_test[@name=ziparchive-tests] /cc_test[@name=ziparchive-tests]/target/host

include $(call select_from_repositories,lib/mk/android-prg.inc)
include $(call select_from_repositories,lib/import/import-librwall.mk)

CC_OPT += -Wno-error=unused-variable
LIBS   += gtest libziparchive zlib libutils libbacktrace libargv

TESTDATA = bad_crc.zip declaredlength.zip dummy-update.zip large.zip valid.zip bad_filename.zip crash.apk

$(TARGET): $(INSTALL_DIR)/testdata.tar

$(INSTALL_DIR)/testdata.tar:
	$(VERBOSE)tar cf $@ -C $(ANDROID_BASEDIR)/testdata/ $(TESTDATA)

clean:
	$(VERBOSE)rm testdata.tar
