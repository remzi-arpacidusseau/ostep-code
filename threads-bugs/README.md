
# Common Concurrency Problems

Code examples from the chapter about concurrency problems.
Type `make` to build all examples.

## Atomicity Failure

- `atomicity.c`: Shows how uncareful check-then-use can crash code
- `atomicity_fixed.c`: Shows how to fix the problem with a lock

## Ordering Violation

- `ordering.c`: Shows the ordering problem from the book chapter
- `ordering_fixed.c`: Shows how to fix the problem with a condition variable

## Deadlock

- `deadlock.c`: Shows simple two-cycle deadlock
- `deadlock_run.sh`: Script to run the above program many times, until you hit a deadlock and are convinced deadlock can occur




