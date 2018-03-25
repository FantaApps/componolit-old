#include <unistd.h>
#include <librwall.h>

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
