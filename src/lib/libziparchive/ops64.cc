#include <unistd.h>
#include <stdio.h>
#include <ops64.h>

extern "C"
ssize_t pread64(int fd, void *buf, size_t count, off_t offset)
{
    size_t remaining = count;
    size_t read = 0;
    char *buffer = (char *)buf;

    while (remaining > 0)
    {
        ssize_t result = pread(fd, buffer + read, remaining, offset + read);

        // End of file
        if (result == 0) break;

        // Error
        if (result < 0) return result;

        remaining -= result;
        read += result;
    }
    return read;
}

extern "C"
off64_t lseek64(int fd, off64_t offset, int whence)
{
    return lseek(fd, offset, whence);
}
