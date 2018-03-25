vpath %.c $(call select_from_repositories,src/lib/librwall)

SRC_C += librwall.c
LIBS += libc
SHARED_LIB = yes

include $(call select_from_repositories,lib/import/import-librwall.mk)
