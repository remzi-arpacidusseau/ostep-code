
# Condition Variables

Code examples from condition variables chapter. Build by typing `make`;
run the resulting executable to see how it works. Insert `sleep()` calls
of various lengths to control timing and force bad things to happen.

## Fork/Join Problem

- `join_spin.c`: Working solution but wastes CPU.
- `join_no_lock.c`: What happens when you don't put a lock around the state change and signal
- `join_no_state_var.c`: What happens if you don't have a state variable
- `join.c`: A working solution
- `join_modular.c`: A modularized version

## Producer/Consumer Problem
- `pc_single_cv.c`: What happens if you only use one condition variable
- `pc.c`: A working solution

