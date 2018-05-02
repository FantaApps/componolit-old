#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

int
main (int argc, char **argv)
{
    int fd, rv;

    for (int i = 0; i < argc; i++) { printf("%d: %s\n", i, argv[i]); }

    if (argc != 3)
    {
        printf ("Invalid arguments: argc==%d\n", argc);
        exit(1);
    }

    fd = open(argv[1], O_RDWR|O_CREAT);
    if (fd < 0)
    {
        printf ("Error opening %s: %s\n", argv[1], strerror(errno));
        exit(2);
    }

    rv = write(fd, argv[2], strlen(argv[2]));
    if (rv < 0)
    {
        printf ("write(): %s\n", strerror(errno));
        exit(3);
    }

    char *var = getenv ("ENVVAR");
    if (var) printf ("ENVVAR=%s", var);

    close(fd);
    exit(0);
}
