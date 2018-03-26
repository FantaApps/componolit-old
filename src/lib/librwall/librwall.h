#pragma once

#include <unistd.h>

#ifdef __cplusplus
extern "C" {
#endif
ssize_t rwall_write(int fd, const void *b, size_t c);
ssize_t rwall_pread(int fd, void *buf, size_t count, off_t offset);

#ifdef __cplusplus
}
#endif
