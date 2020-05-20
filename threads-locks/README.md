
A simple example of compare-and-swap shown in actual C code (which calls into
assembly).

The code, in entirety, is shown here:

```c
#include <stdio.h>

int global = 0;

char compare_and_swap(int *ptr, int old, int new) {
    unsigned char ret;
    // Note that sete sets a ’byte’ not the word
    __asm__ __volatile__ (
	" lock\n"
	" cmpxchgl %2,%1\n"
	" sete %0\n"
	: "=q" (ret), "=m" (*ptr)
	: "r" (new), "m" (*ptr), "a" (old)
	: "memory");
    return ret;
}

int main(int argc, char *argv[]) {
    printf("before successful cas: %d\n", global);
    int success = compare_and_swap(&global, 0, 100);
    printf("after successful cas: %d (success: %d)\n", global, success);
    
    printf("before failing cas: %d\n", global);
    success = compare_and_swap(&global, 0, 200);
    printf("after failing cas: %d (old: %d)\n", global, success);

    return 0;
}
```

The first call to `compare_and_swap()` succeeds because the old value is
correct; the second call does not because the old value is wrong.

To compile and run:
```sh
prompt> gcc -o compare-and-swap compare-and-swap.c -Wall
prompt> ./compare-and-swap
```



