# Overview

Code from OSTEP chapter [Introduction](http://pages.cs.wisc.edu/~remzi/OSTEP/intro.pdf).

To compile, just type:
```
prompt> make
```

See the highly primitive `Makefile` for details.

Then, run them! Examples:

```
prompt> ./cpu A
```

```
prompt> ./mem 1
```

```
prompt> ./threads 10000
```

```
prompt> ./io
```


## Details

One issue with mem.c is that address space randomization is usually on by
default. To turn it off:

### macOS
From [stackoverflow](http://stackoverflow.com/questions/23897963/documented-way-to-disable-aslr-on-os-x)

Just compile/link as follows:
    gcc -o mem mem.c -Wall -Wl,-no_pie

### Linux

From Giovanni Lagorio:

Under Linux you can disable ASLR, without using a debugger, in (at least)  two ways:
* Use the command setarch to run a process with ASLR disabled; I typically run
  bash, with which I can execute examples, like this:
  `setarch $(uname --machine) --addr-no-randomize /bin/bash`
* Writing 0 into `/proc/sys/kernel/randomize_va_space`; you need to be
  root to do this and this change has (a non-permanent) effect on the
  whole system, which is something you probably don't want. I use this
  one only inside VMs.



