#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <err.h>
#include <stdlib.h>

int
main(int argc, char **argv)
{
    off_t offset;
    ssize_t bytes;
    char buffer[65557];

    int fd = open("core-oj-hostdex.jar", O_RDONLY);
    if (fd < 0) err(1, "open");

    offset = lseek(fd, 0, SEEK_END);
    if (offset < 0) err(2, "lseek");

    bytes = pread(fd, buffer, sizeof(buffer), offset - sizeof(buffer));
    if (bytes < 0) err(3, "pread");

    if (bytes < sizeof(buffer)) {
        printf("Short read read=%ld, buffer=%ld\n", bytes, sizeof(buffer));
        exit(1);
    }

    exit(0);
}
