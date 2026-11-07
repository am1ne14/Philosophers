# Philosophers

This is a thread-based solution to the dining philosophers problem. Each
philosopher is a thread, each fork is a mutex, and the program stops when a
philosopher dies or when every philosopher has eaten the optional number of
meals.

The source code is in the `philo/` directory.

## Build and run

```sh
cd philo
make
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep \
  [number_of_times_each_philosopher_must_eat]
```

Example:

```sh
./philo 5 800 200 200 7
```

This starts five philosophers. A philosopher dies after 800 ms without eating,
eating and sleeping each take 200 ms, and the simulation stops once everyone
has eaten seven times. The last argument is optional.

## Implementation

`t_table` holds the shared simulation state: the fork array, timing values,
the finish flag, and the philosopher array. Each `t_philo` stores its own
thread, fork pointers, last meal time, meal count, and a `philo_mutex` that
protects those two per-philosopher values.

The program also uses three table-level mutexes:

- `state_mutex` protects `finished` and prevents actions from being printed
  after the simulation ends.
- `print` keeps status lines from different threads from being mixed together.
- `start_mutex` holds new threads at a start barrier until all philosopher
  threads have been created.

### Fork ordering

Before taking forks, `set_fork_order` chooses a consistent order based on the
philosopher's ID and its neighbour. This means neighbouring philosophers do
not all wait for the same second fork, avoiding the circular wait that causes
the usual deadlock. `take_forks` also tracks which forks were successfully
locked so `unlock_forks` can safely release only those forks.

Even-numbered philosophers wait for half of `time_to_eat` before starting.
For an odd number of philosophers, the thinking phase may add another eating
duration when eating is at least as long as sleeping. These delays spread the
fork requests out instead of starting every thread at the same moment.

### Monitoring

The main thread runs `monitor_philos` after releasing the start barrier. It
checks every philosopher roughly every 50 microseconds. `check_death` compares
the current time against `last_meal` while holding that philosopher's mutex.
When the timeout is reached it sets `finished` under `state_mutex` and prints
the single `died` line. When a meal limit was supplied, the monitor also stops
the simulation after every philosopher reaches it.

There is a dedicated single-philosopher routine. It prints one fork message,
waits for `time_to_die`, and lets the monitor report the death instead of
trying to lock the same fork twice.

## Output

Actions are printed as:

```text
timestamp_in_ms philosopher_id action
```

The program reports taking forks, eating, sleeping, thinking, and death. All
timestamps are measured from the shared simulation start time.
