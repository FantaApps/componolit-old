LIBCORE_DIR = $(call select_from_ports,libcore)/libcore
LIBOPENJDK_INCLUDE = $(LIBCORE_DIR)/include

vpath %.cpp $(LIBCORE_DIR)
vpath %.c $(LIBCORE_DIR)
INC_DIR += $(LIBCORE_DIR)/include
INC_DIR += $(LIBOPENJDK_DIR)/ojluni/src/main/native/
