#ifndef _INCLUDE_OPS64_H_
#define _INCLUDE_OPS64_H_

#include <unistd.h>

extern "C"
ssize_t pread64(int fd, void *buf, size_t count, off_t offset);

extern "C"
off64_t lseek64(int fd, off64_t offset, int whence);

#endif // _INCLUDE_OPS64_H_
