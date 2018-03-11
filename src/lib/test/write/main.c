#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

int
main (int argc, char **argv)
{
    int fd, rv;

    if (argc != 3)
    {
        printf ("Invalid arguments: argc==%d\n", argc);
        return 1;
    }

    fd = open(argv[1], O_RDWR|O_CREAT);
    if (fd < 0)
    {
        printf ("Error opening %s: %s\n", argv[1], strerror(errno));
        return 2;
    }

    rv = write(fd, argv[2], strlen(argv[2]));
    if (rv < 0)
    {
        printf ("write(): %s\n", strerror(errno));
        return 3;
    }

    close(fd);
    return 0;
}
