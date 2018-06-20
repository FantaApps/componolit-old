TARGET = thttpd
THTTPD_DIR := $(call select_from_ports,thttpd)/src

GENDIR = $(BUILD_BASE_DIR)/bin
SRC_C = fdwatch.c libhttpd.c match.c mmc.c tdate_parse.c thttpd.c timers.c
SRC_CC = libargv.cc

$(warning $(PRG_DIR))
vpath %.cc $(PRG_DIR)
vpath %.c $(THTTPD_DIR)
vpath %.txt $(THTTPD_DIR)

INC_DIR += $(THTTPD_DIR)
CC_OPT += -DHAVE_SELECT -DHAVE_INT64T -DHAVE_FCNTL_H -DHAVE_SOCKLENT -DHAVE_ATOLL -DHAVE_DIRENT_H -DHAVE_TM_GMTOFF
CC_OPT += -I$(GENDIR) -Wno-unused-variable -Wno-unused-but-set-variable

LIBS += libc libm libc_lwip_nic_dhcp
CC_CXX_WARN_STRICT =

$(GENDIR)/mime_encodings.h: $(THTTPD_DIR)/mime_encodings.txt
	rm -f $@
	sed < $< > $@ \
     -e 's/#.*//' -e 's/[  ]*$$//' -e '/^$$/d' \
     -e 's/[   ][    ]*/", 0, "/' -e 's/^/{ "/' -e 's/$$/", 0 },/'
 
$(GENDIR)/mime_types.h: $(THTTPD_DIR)/mime_types.txt
	rm -f $@
	sed < $< > $@ \
     -e 's/#.*//' -e 's/[  ]*$$//' -e '/^$$/d' \
     -e 's/[   ][    ]*/", 0, "/' -e 's/^/{ "/' -e 's/$$/", 0 },/'

all: $(GENDIR)/mime_types.h $(GENDIR)/mime_encodings.h
