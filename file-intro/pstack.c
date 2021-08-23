// Persistent stack example of how mmap() naturally creates a software abstraction of persistent memory.
// Author: Terence Kelly
//         tpkelly @ { acm.org, cs.princeton.edu, eecs.umich.edu }

// Note:  Use 'truncate' to make the initial (empty) backing file,
// whose size should be a multiple of the system page size:
//
//     prompt> getconf PAGESIZE
//     4096
//     prompt> truncate -s 4096 ps.img
//
// makes a 4096-byte empty file.  The first sizeof(size_t) bytes will
// be interprted as the number of items on the stack; the remainder
// of the file will contain the integers contained in the stack.
// Now you can run the program:
//
//     prompt> ./pstack 7 13 47 pop
//     47
//     prompt> ./pstack pop pop 99
//     13
//     7
//     prompt> ./pstack pop
//     99
//
// Notice that items push'd in one invocation of the program persist
// until the next invocation:  The stack is persistent.
//
// You can use hexdump to examine the contents of the backing file:
//
//     prompt> hexdump ps.img

#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>

typedef struct {
    size_t n;
    int stack[]; // zero-length per C99
} pstack_t;

int main(int argc, char *argv[]) {
    int fd, rc;
    struct stat s;
    size_t file_size;
    pstack_t *p;

    fd = open("ps.img", O_RDWR);
    assert(fd > -1);
    rc = fstat(fd, &s);
    assert(rc == 0);

    file_size = (size_t) s.st_size;
    assert(file_size >= sizeof(pstack_t) && file_size % sizeof(int) == 0);

    p = (pstack_t *) mmap(NULL, file_size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    assert(p != MAP_FAILED);

    for (int i = 1; i < argc; i++)
        if (strcmp(argv[i], "pop") == 0) {
            if (p->n > 0)  // stack not empty
                printf("%d\n", p->stack[--p->n]);
        } else { // push
          if (sizeof(pstack_t) + (1 + p->n) * sizeof(int) <= file_size) // stack not full
                p->stack[p->n++] = atoi(argv[i]);
        }
    (void) close(fd);
    return 0;
}
