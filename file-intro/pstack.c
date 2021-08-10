// Persistent stack example of how mmap() naturally creates a software abstraction of persistent memory.
// Author: Terence Kelly <tpklly@acm.org>

// Note: Use 'dd' to make the initial (empty) image, e.g., 
//   dd if=/dev/zero of=ps.img bs=32 count=1
// makes a 32-byte empty file (the first integer being the size of the stack,
// the remaining integers being values)

#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>

int open_or_die(const char *path, int oflag) {
    int fd = open(path, oflag);
    assert(fd > 0);
    return fd;
}

int fstat_or_die(int fildes, struct stat *buf) {
    int rc = fstat(fildes, buf);
    assert(rc == 0);
    return rc;
}

void *mmap_or_die(void *addr, size_t len, int prot, int flags, int fd, off_t offset) {
    void *p = mmap(addr, len, prot, flags, fd, offset);
    assert(p != MAP_FAILED);
    return p;
}

typedef struct {
    size_t n;
    int stack[]; // zero-length per C99
} pstack_t; 

int main(int argc, char *argv[]) {
    int fd, rc;
    struct stat s;
    size_t file_size;
    pstack_t *p;
    
    fd = open_or_die("ps.img", O_RDWR);
    rc = fstat_or_die(fd, &s);

    file_size = (size_t) s.st_size;
    assert(file_size % sizeof(int) == 0);

    p = mmap_or_die(NULL, file_size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);

    for (int i = 1; i < argc; i++)
	if (strcmp(argv[i], "pop") == 0) {  
	    if (p->n > 0)  // stack not empty
		printf("%d\n", p->stack[--p->n]);
	    else
		printf("stack empty\n");
	} else
	    if (sizeof(pstack_t) + p->n * sizeof(int) < file_size)  // stack not full
		p->stack[p->n++] = atoi(argv[i]);
	    else
		printf("stack full: %d not added\n", atoi(argv[i]));

    close(fd);
    return 0;
}
