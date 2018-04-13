#ifndef _BYTESWAP_H_
#define _BYTESWAP_H_

#include <sys/endian.h>

#include <stdlib.h>

// Bogus posix_memalign implementation
// libjavacore test cases only use 8 as alignment which should be fulfilled
// by malloc() by default.
inline
int posix_memalign(void **memptr, size_t alignment, size_t size)
{
    *memptr = malloc(size);
    if ((unsigned long)*memptr % alignment) return -1;
    return 0;
};

#define bswap_16 bswap16
#define bswap_32 bswap32

#endif // _BYTESWAP_H_
