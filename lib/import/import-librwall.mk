LIBRWALL_DIR = $(call select_from_repositories,src/lib/librwall)

CC_OPT += -Dpread64=rwall_pread
CC_OPT += -Dlseek64=lseek
CC_OPT += -include $(LIBRWALL_DIR)/librwall.h

INC_DIR += $(LIBRWALL_DIR)
