// mmap() tests
//
// This runs on Linux. In this directory, do:
// $ make LDFLAGS=-lz
// $ ./mmap

#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include <zlib.h>

enum
{
    SIZE_SMALL           =   42,
    SIZE_PAGE            = 4096,
    SIZE_PAGE_PLUS       = 5000,
    SIZE_MULTI_PAGE      = 8192,
    SIZE_MULTI_PAGE_PLUS = 9000
};

const char testfile[] = "test.dat";

bool test_mmap (const char *prefix, const char *test_name, int fd, int size, void *addr, bool read, bool write, bool exec, unsigned long crc)
{
    int prot = (read ? PROT_READ : 0) | (write ? PROT_WRITE : 0) | (exec ? PROT_EXEC : 0);
    int flags = (fd == -1 ? MAP_ANON : 0) | MAP_PRIVATE;

    void *result = mmap (addr, size, prot, flags, fd, 0);
    printf("%p = mmap (addr=%p, size=%d, prot=%d, flags=%x, fd=%d, 0), crc=%lx\n", result, addr, size, prot, flags, fd, crc);
    if (result == MAP_FAILED)
    {
        printf("%s%s: FAILED (mmap: %s)\n", prefix, test_name, strerror(errno));
        return false;
    }

    if (addr)
    {
        if (addr != result)
        {
            printf("%s%s: FAILED (fixed address: expected=%p got=%p)\n", prefix, test_name, addr, result);
            return false;
        }
    }

    if (write)
    {
        if (fd == -1)
        {
            memset (result, 'x', size);
        }

        if (read && crc)
        {
            unsigned long checksum = crc32(0L, Z_NULL, 0);
            checksum = crc32(checksum, (const unsigned char*)result, size);
            if (checksum != crc)
            {
                munmap(result, size);
                printf("%s%s: FAILED (checksum: expected=%lx got=%lx)\n", prefix, test_name, crc, checksum);
                return false;
            }
        }
    }


    if (munmap(result, size) < 0)
    {
        printf("%s%s: FAILED (munmap: %s)\n", prefix, test_name, strerror(errno));
        return false;
    };

    printf("%s%s: OK\n", prefix, test_name);
    return true;
}

bool
test_file(const char *prefix, const char *test_name, int size, void *addr, bool read, bool write, bool exec, unsigned long crc)
{
    int fd = open(testfile, O_RDWR);
    if (fd < 0)
    {
        printf("%s: ERROR opening test file %s\n", test_name, testfile);
        return false;
    }

    bool result = test_mmap(prefix, test_name, fd, size, addr, read, write, exec, crc);
    close (fd);
    return result;
}

bool
test_all (const char *prefix, unsigned long a)
{
    void *addr = (void *)a;
    bool success = true;

    success &= test_mmap(prefix, "ANON/SMALL /---", -1, SIZE_SMALL, addr, false, false, false, 0);
    success &= test_mmap(prefix, "ANON/SMALL /--x", -1, SIZE_SMALL, addr, false, false, true,  0);
    success &= test_mmap(prefix, "ANON/SMALL /-w-", -1, SIZE_SMALL, addr, false, true,  false, 0);
    success &= test_mmap(prefix, "ANON/SMALL /-wx", -1, SIZE_SMALL, addr, false, true,  true,  0);
    success &= test_mmap(prefix, "ANON/SMALL /r--", -1, SIZE_SMALL, addr, true,  false, false, 0);
    success &= test_mmap(prefix, "ANON/SMALL /r-x", -1, SIZE_SMALL, addr, true,  false, true,  0);
    success &= test_mmap(prefix, "ANON/SMALL /rw-", -1, SIZE_SMALL, addr, true,  true,  false, 0xcb5f7c02);
    success &= test_mmap(prefix, "ANON/SMALL /rwx", -1, SIZE_SMALL, addr, true,  true,  true,  0xcb5f7c02);

    success &= test_mmap(prefix, "ANON/PAGE  /---", -1, SIZE_PAGE, addr, false, false, false, 0);
    success &= test_mmap(prefix, "ANON/PAGE  /--x", -1, SIZE_PAGE, addr, false, false, true,  0);
    success &= test_mmap(prefix, "ANON/PAGE  /-w-", -1, SIZE_PAGE, addr, false, true,  false, 0);
    success &= test_mmap(prefix, "ANON/PAGE  /-wx", -1, SIZE_PAGE, addr, false, true,  true,  0);
    success &= test_mmap(prefix, "ANON/PAGE  /r--", -1, SIZE_PAGE, addr, true,  false, false, 0);
    success &= test_mmap(prefix, "ANON/PAGE  /r-x", -1, SIZE_PAGE, addr, true,  false, true,  0);
    success &= test_mmap(prefix, "ANON/PAGE  /rw-", -1, SIZE_PAGE, addr, true,  true,  false, 0x3e1077c1);
    success &= test_mmap(prefix, "ANON/PAGE  /rwx", -1, SIZE_PAGE, addr, true,  true,  true,  0x3e1077c1);

    success &= test_mmap(prefix, "ANON/PAGE+ /---", -1, SIZE_PAGE_PLUS, addr, false, false, false, 0);
    success &= test_mmap(prefix, "ANON/PAGE+ /--x", -1, SIZE_PAGE_PLUS, addr, false, false, true,  0);
    success &= test_mmap(prefix, "ANON/PAGE+ /-w-", -1, SIZE_PAGE_PLUS, addr, false, true,  false, 0);
    success &= test_mmap(prefix, "ANON/PAGE+ /-wx", -1, SIZE_PAGE_PLUS, addr, false, true,  true,  0);
    success &= test_mmap(prefix, "ANON/PAGE+ /r--", -1, SIZE_PAGE_PLUS, addr, true,  false, false, 0);
    success &= test_mmap(prefix, "ANON/PAGE+ /r-x", -1, SIZE_PAGE_PLUS, addr, true,  false, true,  0);
    success &= test_mmap(prefix, "ANON/PAGE+ /rw-", -1, SIZE_PAGE_PLUS, addr, true,  true,  false, 0x00dbf026);
    success &= test_mmap(prefix, "ANON/PAGE+ /rwx", -1, SIZE_PAGE_PLUS, addr, true,  true,  true,  0x00dbf026);

    success &= test_mmap(prefix, "ANON/MPAGE /---", -1, SIZE_MULTI_PAGE, addr, false, false, false, 0);
    success &= test_mmap(prefix, "ANON/MPAGE /--x", -1, SIZE_MULTI_PAGE, addr, false, false, true,  0);
    success &= test_mmap(prefix, "ANON/MPAGE /-w-", -1, SIZE_MULTI_PAGE, addr, false, true,  false, 0);
    success &= test_mmap(prefix, "ANON/MPAGE /-wx", -1, SIZE_MULTI_PAGE, addr, false, true,  true,  0);
    success &= test_mmap(prefix, "ANON/MPAGE /r--", -1, SIZE_MULTI_PAGE, addr, true,  false, false, 0);
    success &= test_mmap(prefix, "ANON/MPAGE /r-x", -1, SIZE_MULTI_PAGE, addr, true,  false, true,  0);
    success &= test_mmap(prefix, "ANON/MPAGE /rw-", -1, SIZE_MULTI_PAGE, addr, true,  true,  false, 0x123905c5);
    success &= test_mmap(prefix, "ANON/MPAGE /rwx", -1, SIZE_MULTI_PAGE, addr, true,  true,  true,  0x123905c5);

    success &= test_mmap(prefix, "ANON/MPAGE+/---", -1, SIZE_MULTI_PAGE_PLUS, addr, false, false, false, 0);
    success &= test_mmap(prefix, "ANON/MPAGE+/--x", -1, SIZE_MULTI_PAGE_PLUS, addr, false, false, true,  0);
    success &= test_mmap(prefix, "ANON/MPAGE+/-w-", -1, SIZE_MULTI_PAGE_PLUS, addr, false, true,  false, 0);
    success &= test_mmap(prefix, "ANON/MPAGE+/-wx", -1, SIZE_MULTI_PAGE_PLUS, addr, false, true,  true,  0);
    success &= test_mmap(prefix, "ANON/MPAGE+/r--", -1, SIZE_MULTI_PAGE_PLUS, addr, true,  false, false, 0);
    success &= test_mmap(prefix, "ANON/MPAGE+/r-x", -1, SIZE_MULTI_PAGE_PLUS, addr, true,  false, true,  0);
    success &= test_mmap(prefix, "ANON/MPAGE+/rw-", -1, SIZE_MULTI_PAGE_PLUS, addr, true,  true,  false, 0x128b71d4);
    success &= test_mmap(prefix, "ANON/MPAGE+/rwx", -1, SIZE_MULTI_PAGE_PLUS, addr, true,  true,  true,  0x128b71d4);

    success &= test_file(prefix, "FILE/SMALL /---", SIZE_SMALL, addr, false, false, false, 0);
    success &= test_file(prefix, "FILE/SMALL /--x", SIZE_SMALL, addr, false, false, true,  0);
    // success &= test_file(prefix, "FILE/SMALL /-w-", SIZE_SMALL, addr, false, true,  false, 0x44cae937);
    // success &= test_file(prefix, "FILE/SMALL /-wx", SIZE_SMALL, addr, false, true,  true,  0x44cae937);
    success &= test_file(prefix, "FILE/SMALL /r--", SIZE_SMALL, addr, true,  false, false, 0x44cae937);
    success &= test_file(prefix, "FILE/SMALL /r-x", SIZE_SMALL, addr, true,  false, true,  0x44cae937);
    // success &= test_file(prefix, "FILE/SMALL /rw-", SIZE_SMALL, addr, true,  true,  false, 0x44cae937);
    // success &= test_file(prefix, "FILE/SMALL /rwx", SIZE_SMALL, addr, true,  true,  true,  0x44cae937);

    success &= test_file(prefix, "FILE/PAGE  /---", SIZE_PAGE, addr, false, false, false, 0);
    success &= test_file(prefix, "FILE/PAGE  /--x", SIZE_PAGE, addr, false, false, true,  0);
    // success &= test_file(prefix, "FILE/PAGE  /-w-", SIZE_PAGE, addr, false, true,  false, 0);
    // success &= test_file(prefix, "FILE/PAGE  /-wx", SIZE_PAGE, addr, false, true,  true,  0);
    success &= test_file(prefix, "FILE/PAGE  /r--", SIZE_PAGE, addr, true,  false, false, 0x211de2e4);
    success &= test_file(prefix, "FILE/PAGE  /r-x", SIZE_PAGE, addr, true,  false, true,  0x211de2e4);
    // success &= test_file(prefix, "FILE/PAGE  /rw-", SIZE_PAGE, addr, true,  true,  false, 0x211de2e4);
    // success &= test_file(prefix, "FILE/PAGE  /rwx", SIZE_PAGE, addr, true,  true,  true,  0x211de2e4);

    success &= test_file(prefix, "FILE/PAGE+ /---", SIZE_PAGE_PLUS, addr, false, false, false, 0);
    success &= test_file(prefix, "FILE/PAGE+ /--x", SIZE_PAGE_PLUS, addr, false, false, true,  0);
    // success &= test_file(prefix, "FILE/PAGE+ /-w-", SIZE_PAGE_PLUS, addr, false, true,  false, 0);
    // success &= test_file(prefix, "FILE/PAGE+ /-wx", SIZE_PAGE_PLUS, addr, false, true,  true,  0);
    success &= test_file(prefix, "FILE/PAGE+ /r--", SIZE_PAGE_PLUS, addr, true,  false, false, 0x49019fbe);
    success &= test_file(prefix, "FILE/PAGE+ /r-x", SIZE_PAGE_PLUS, addr, true,  false, true,  0x49019fbe);
    // success &= test_file(prefix, "FILE/PAGE+ /rw-", SIZE_PAGE_PLUS, addr, true,  true,  false, 0x49019fbe);
    // success &= test_file(prefix, "FILE/PAGE+ /rwx", SIZE_PAGE_PLUS, addr, true,  true,  true,  0x49019fbe);

    success &= test_file(prefix, "FILE/MPAGE /---", SIZE_MULTI_PAGE, addr, false, false, false, 0);
    success &= test_file(prefix, "FILE/MPAGE /--x", SIZE_MULTI_PAGE, addr, false, false, true,  0);
    // success &= test_file(prefix, "FILE/MPAGE /-w-", SIZE_MULTI_PAGE, addr, false, true,  false, 0);
    // success &= test_file(prefix, "FILE/MPAGE /-wx", SIZE_MULTI_PAGE, addr, false, true,  true,  0);
    success &= test_file(prefix, "FILE/MPAGE /r--", SIZE_MULTI_PAGE, addr, true,  false, false, 0x79490216);
    success &= test_file(prefix, "FILE/MPAGE /r-x", SIZE_MULTI_PAGE, addr, true,  false, true,  0x79490216);
    // success &= test_file(prefix, "FILE/MPAGE /rw-", SIZE_MULTI_PAGE, addr, true,  true,  false, 0x79490216);
    // success &= test_file(prefix, "FILE/MPAGE /rwx", SIZE_MULTI_PAGE, addr, true,  true,  true,  0x79490216);

    success &= test_file(prefix, "FILE/MPAGE+/---", SIZE_MULTI_PAGE_PLUS, addr, false, false, false, 0);
    success &= test_file(prefix, "FILE/MPAGE+/--x", SIZE_MULTI_PAGE_PLUS, addr, false, false, true,  0);
    // success &= test_file(prefix, "FILE/MPAGE+/-w-", SIZE_MULTI_PAGE_PLUS, addr, false, true,  false, 0);
    // success &= test_file(prefix, "FILE/MPAGE+/-wx", SIZE_MULTI_PAGE_PLUS, addr, false, true,  true,  0);
    success &= test_file(prefix, "FILE/MPAGE+/r--", SIZE_MULTI_PAGE_PLUS, addr, true,  false, false, 0x1975681b);
    success &= test_file(prefix, "FILE/MPAGE+/r-x", SIZE_MULTI_PAGE_PLUS, addr, true,  false, true,  0x1975681b);
    // success &= test_file(prefix, "FILE/MPAGE+/rw-", SIZE_MULTI_PAGE_PLUS, addr, true,  true,  false, 0x1975681b);
    // success &= test_file(prefix, "FILE/MPAGE+/rwx", SIZE_MULTI_PAGE_PLUS, addr, true,  true,  true,  0x1975681b);

    return success;
}

int
main(int argc __attribute__((unused)), char **argv __attribute((unused)))
{
    bool success = true;

    success &= test_all ("FIXED ADDRESS/", 0xdead0000);
    success &= test_all (" AUTO ADDRESS/", 0);
    exit (success ? 0 : 1);
}
