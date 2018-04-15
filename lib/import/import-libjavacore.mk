INC_DIR += $(call select_from_repositories,src/lib/libjavacore)

LIBCORE_DIR = $(call select_from_ports,libcore)/libcore
LIBCORE_INCLUDE = $(LIBCORE_DIR)/include
PTHREAD_DIR = $(call select_from_repositories,src/lib/pthread)

vpath %.cpp $(LIBCORE_DIR)
INC_DIR += $(LIBCORE_DIR) $(LIBCORE_INCLUDE) $(PTHREAD_DIR)

OPT_CC += -DU_USING_ICU_NAMESPACE=0
