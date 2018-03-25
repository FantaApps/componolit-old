#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

#define error(fmt,...) { printf(fmt ": %s\n", ##__VA_ARGS__, strerror(errno)); return -1; };
#define errorx(fmt,...) { printf(fmt "\n", ##__VA_ARGS__); return -1; };

#define BYTES 30

int
main(int argc, char **argv)
{
    int fd;
    char buffer[65536];
    ssize_t result;

    if (argc != 2) errorx("Insufficient arguments");

    fd = open(argv[1], O_RDONLY);
    if (fd < 0) error("opening %s", argv[1]);

    for (;;)
    {
        result = read(fd, buffer, sizeof(buffer));
        if (result < 0) error("read");
        if (result == 0) exit(0);

        for (size_t i = 0; i < result; i++)
        {
            printf(" %2.2x", buffer[i] & 0xff);
            if (i % BYTES == (BYTES-1)) printf("\n");
        }
        printf("\n");

    }
}
