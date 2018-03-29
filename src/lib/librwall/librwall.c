#include <unistd.h>
#include <librwall.h>

// We want to use libc versions, not our own macros.
#undef pread
#undef pread64

ssize_t
rwall_write(int fd, const void *b, size_t c)
{
    size_t  remaining = c;
    char *buffer = (char *)b;
    int result = 0;

    do {
        result = write(fd, buffer, remaining);
        if (result < 0)
        {
            return result;
        }

        remaining -= result;
        buffer += result;

    } while (result > 0 && remaining > 0);

    return (c - remaining);
};

ssize_t rwall_pread(int fd, void *buf, size_t count, off_t offset)
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
