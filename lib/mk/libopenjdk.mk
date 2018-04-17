SRC_C = \
    ojluni/src/main/native/java_util_zip_ZipFile.c \
    ojluni/src/main/native/java_util_zip_Inflater.c \
    ojluni/src/main/native/java_util_zip_Deflater.c \
    ojluni/src/main/native/java_util_zip_CRC32.c \
    ojluni/src/main/native/Adler32.c \
    ojluni/src/main/native/zip_util.c \
    ojluni/src/main/native/jni_util.c \
    ojluni/src/main/native/jni_util_md.c \
    ojluni/src/main/native/io_util.c \
    ojluni/src/main/native/canonicalize_md.c \
    ojluni/src/main/native/FileDescriptor_md.c \
    ojluni/src/main/native/DatagramChannelImpl.c \
    ojluni/src/main/native/DatagramDispatcher.c \
    ojluni/src/main/native/Console_md.c \
    ojluni/src/main/native/IOUtil.c \
    ojluni/src/main/native/PollArrayWrapper.c \
    ojluni/src/main/native/SocketChannelImpl.c \
    ojluni/src/main/native/FileChannelImpl.c \
    ojluni/src/main/native/FileDispatcherImpl.c \
    ojluni/src/main/native/FileOutputStream_md.c \
    ojluni/src/main/native/FileInputStream.c \
    ojluni/src/main/native/FileSystemPreferences.c \
    ojluni/src/main/native/UnixAsynchronousServerSocketChannelImpl.c \
    ojluni/src/main/native/UnixAsynchronousSocketChannelImpl.c \
    ojluni/src/main/native/io_util_md.c \
    ojluni/src/main/native/NativeThread.c \
    ojluni/src/main/native/FileKey.c \
    ojluni/src/main/native/UnixFileSystem_md.c \
    ojluni/src/main/native/ObjectStreamClass.c \
    ojluni/src/main/native/ObjectOutputStream.c \
    ojluni/src/main/native/ObjectInputStream.c \
    ojluni/src/main/native/UnixCopyFile.c \
    ojluni/src/main/native/UnixNativeDispatcher.c \
    ojluni/src/main/native/InetAddress.c \
    ojluni/src/main/native/net_util.c \
    ojluni/src/main/native/net_util_md.c \
    ojluni/src/main/native/Net.c \
    ojluni/src/main/native/MappedByteBuffer.c \
    ojluni/src/main/native/Inet6Address.c \
    ojluni/src/main/native/Inet4Address.c \
    ojluni/src/main/native/ServerSocketChannelImpl.c \
    ojluni/src/main/native/SocketInputStream.c \
    ojluni/src/main/native/SocketOutputStream.c \
    ojluni/src/main/native/Float.c \
    ojluni/src/main/native/Double.c \
    ojluni/src/main/native/StrictMath.c \
    ojluni/src/main/native/Math.c \
    ojluni/src/main/native/ProcessEnvironment_md.c \
    ojluni/src/main/native/System.c \
    ojluni/src/main/native/Runtime.c \
    ojluni/src/main/native/UNIXProcess_md.c \
    ojluni/src/main/native/Bits.c \

SRC_CC = \
    ojluni/src/main/native/linux_close.cpp \
    ojluni/src/main/native/Character.cpp \
    ojluni/src/main/native/Register.cpp \
    ojluni/src/main/native/socket_tagger_util.cpp

CC_OPT += -D__GENODE__
CC_OPT += -D__SIGRTMIN=0
CC_OPT += -Dseek64=seek
CC_OPT += -Dlseek64=lseek
CC_OPT += -Dmmap64=mmap
CC_OPT += -Dpread64=pread
CC_OPT += -Dpwrite64=pwrite
CC_OPT += -Dftruncate64=ftruncate
CC_OPT += -Dstat64=stat
CC_OPT += -Dfstat64=fstat
CC_OPT += -Dflock64=flock
CC_OPT += -Doff64_t=off_t
CC_OPT += -Dreaddir64=readdir
CC_OPT += -Dreaddir64_r=readdir_r
CC_OPT += -Dstatvfs64=statvfs
CC_OPT += -Ddirent64=dirent
CC_OPT += -Dopen64=open
CC_OPT += -Dlstat64=lstat
CC_OPT += -DF_SETLK64=F_SETLK
CC_OPT += -DF_SETLKW64=F_SETLKW
CC_OPT += -DO_CLOEXEC=0

# Disable some warning
CC_OPT += -Wno-maybe-uninitialized
CC_OPT += -Wno-unused-variable
CC_OPT += -Wno-uninitialized
CC_OPT += -Wno-unused-but-set-variable
CC_OPT += -Wno-unused-function
CC_OPT += -Werror

LIBS += libicuuc zlib boringssl stdcxx libopenjdkjvm libnativehelper libc liblog fdlibm

include $(call select_from_repositories,lib/import/import-libopenjdk.mk)

SHARED_LIB = yes
CC_CXX_WARN_STRICT =
