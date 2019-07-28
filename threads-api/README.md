
# Threads API

Some simple examples of how to use POSIX thread APIs.

Relevant files:
- `thread_create.c`: A simple thread creation program, with args passed to the
thread. 
- `thread_create_with_return_args.c`: Return values from the thread to the
parent.
- `thread_create_simple_args.c`: Simpler argument/return value passing for the
lazy. 

Type `make` to build; each file `foo.c` generates an executable `foo` which
you can then run, e.g.:

```sh
prompt> ./thread_create
```

