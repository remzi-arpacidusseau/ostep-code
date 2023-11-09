
# Fork/Join

Simple example of the fork/join (i.e., waiting for a child) problem
using semaphores, found in `join.c`.

Run `make` to build the code; run `join` to test it. Fun!

```sh
prompt> make
prompt> ./join
```


# Binary Semaphores (Locks)

Simple example of semaphores as locks (binary semaphores).
Code in `binary.c`.

Run `make` to build the code; run `binary` to test it. Fun!

```sh
prompt> make
prompt> ./binary
```

# Producer/Consumer

Code for the working producer/consumer solution from the text,
found in `producer_consumer.c`.

Run `make` to build, and `producer_consumer` to test it.
The program takes a few different arguments:
- The number of buffers between the producer/consumer
- The number of times a producer should produce something
- The number of consumer threads

```sh
prompt> make
prompt> ./producer_consumer 1 1000 1
```

The output should print each produced item once, and show which
consumer consumed each produced item.

# Reader/Writer Locks

Code in `rwlock.c`. Build via `make`, run via `rwlock`.

# Dining Philosophers

The dining philosophers example from the text is found herein, in a few
different forms:
- `dining_philosophers_deadlock.c`: code with deadlock
- `dining_philosophers_deadlock_print.c`: code with deadlock, and some useful printing
- `dining_philosophers_no_deadlock.c`: code without deadlock
- `dining_philosophers_no_deadlock_print.c`: code without deadlock, and some useful printing

Run `make` to build all of them with the highly primitive `Makefile`.


# Zemaphores

Code in `zemaphore.c`. We bet you can figure out the rest. This is just
a small test of the Zemaphore with the fork/join problem.


# Throttle

Bonus code that shows how semaphores can be used to throttle how 
many different threads run through a certain bit of code at a time.
Code in `throttle.c`. 

