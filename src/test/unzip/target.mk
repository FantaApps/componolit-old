TARGET = unzip
UNZIP_DIR = $(call select_from_ports,unzip)/unzip

SRC_C = \
	crc32.c \
	crypt.c \
	envargs.c \
	explode.c \
	extract.c \
	fileio.c \
	globals.c \
	inflate.c \
	list.c \
	match.c \
	process.c \
	ttyio.c \
	unix/unix.c \
	unshrink.c \
	unzip.c \
	zipinfo.c \

INC_DIR += $(call select_from_repositories,src/lib/test/unzip)
INC_DIR += $(UNZIP_DIR)
vpath %.c $(UNZIP_DIR) $(UNZIP_DIR)/unix

CC_OPT += -DNO_LCHMOD -DNO_LCHOWN

LIBS += libc libargv
