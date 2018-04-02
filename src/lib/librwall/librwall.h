#ifndef _LIBRWALL_H_
#define _LIBRWALL_H_

#ifndef __ASSEMBLER__

#include <unistd.h>

#define pread64(fd,buf,count,off) rwall_pread(fd,buf,count,off)
#define pread(fd,buf,count,off) rwall_pread(fd,buf,count,off)
#define lseek64(fd,off,whence) lseek(fd,off,whence)
#define ftruncate64(fd,len) ftruncate(fd,len)

#ifdef __cplusplus
extern "C" {
#endif
ssize_t rwall_write(int fd, const void *b, size_t c);
ssize_t rwall_pread(int fd, void *buf, size_t count, off_t offset);

#ifdef __cplusplus
}
#endif

#endif // __ASSEMBLER__
#endif // _LIBRWALL_H_
