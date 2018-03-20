/*
 * \brief  Simple file compare tool
 * \author Alexander Senier
 * \date   2018-03-20
 */

/*
 * Copyright (C) 2018 Componolit GmbH
 *
 * This file is part of the Componolit platform, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define error(fmt,...) { printf(fmt ": %s\n", ##__VA_ARGS__, strerror(errno)); return -1; };
#define errorx(fmt,...) { printf(fmt "\n", ##__VA_ARGS__); return -1; };

static int
cmp(char *lpath, char *rpath)
{
    int lfd, rfd;

    enum { BUFSIZE = 4096 };
    unsigned char lbuf[BUFSIZE], rbuf[BUFSIZE];
    ssize_t lfill = 0, rfill = 0;
    int rpos = 1, lpos = 1, pos = 0;

    lfd = open(lpath, O_RDONLY);
    if (lfd < 0) error("open %s", lpath);

    rfd = open(rpath, O_RDONLY);
    if (rfd < 0) error("open %s", rpath);

    for (;;)
    {
        if (lpos >= lfill)
        {
            lfill = read(lfd, lbuf, sizeof(lbuf));
            if (lfill < 0) error("reading %s", lpath);
            lpos = 0;
        }

        if (rpos >= rfill)
        {
            rfill = read(rfd, rbuf, sizeof(rbuf));
            if (rfill < 0) error("reading %s", rpath);
            rpos = 0;
        }

        if (lfill == 0 && rfill  > 0) errorx("%s is longer", rpath);
        if (lfill  > 0 && rfill == 0) errorx("%s is longer", lpath);

        // Done
        if (lfill == 0 && rfill == 0) return 0;

        while (lpos < lfill && rpos < rfill)
        {
            pos++;
            if (rbuf[rpos] != lbuf[lpos])
            {
                errorx("Mismatch at %d: %2.2x != %2.2x", pos, rbuf[rpos], lbuf[lpos]);
            };
            ++rpos;
            ++lpos;
        }
    }
}

int
test()
{
    if (cmp("test1.dat", "/does/not/exist1") == 0) return -1;
    if (cmp("/does/not/exist2", "test1") == 0)     return -1;
    if (cmp("test1.dat", "test1.dat") != 0)        return -1;
    if (cmp("test2.dat", "test2.dat") != 0)        return -1;
    if (cmp("test1.dat", "test2.dat") == 0)        return -1;
    if (cmp("test1.dat", "test1trunc.dat") == 0)   return -1;
    if (cmp("test1trunc.dat", "test1.dat") == 0)   return -1;

    return 0;
}

int
main(int argc, char **argv)
{
    if (argc == 2 && (0 == strncmp(argv[1], "test", 4))) exit (test());
    if (argc != 3) errx(1, "Invalid arguments");
    exit(cmp(argv[1], argv[2]));
}
