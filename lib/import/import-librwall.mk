LIBRWALL_DIR = $(call select_from_repositories,src/lib/librwall)

CC_OPT += -include $(LIBRWALL_DIR)/librwall.h
INC_DIR += $(LIBRWALL_DIR)
