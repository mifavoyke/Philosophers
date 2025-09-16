# Philosophers (Dining Philosophers Problem)

## Demo

<div align="center">
  <video  width="200" src="https://github.com/user-attachments/assets/3e6066be-8dc0-4c1d-bc24-f0eddd188612" autoplay />
</div>

## Goal

Simulate a set of philosophers sitting at a round table who alternately think, eat and sleep while sharing a limited number of forks (one between each pair). The challenge is to coordinate access to forks so that no philosopher starves and data remains consistent (no data races).

## CLI Usage
```
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [meal_goal]
```
All time arguments are in milliseconds.

If `meal_goal` is omitted, simulation runs until a death occurs.

### Example
```
./philo 5 800 200 200 7
```
Runs 5 philosophers; each must eat 7 times or simulation ends sooner if one dies.

### Synchronization Primitives
- `fork` mutexes: one per philosopher (thread)
- `print_mutex`: serialize console output
- `time_mutex`: protect `last_meal_time` updates/reads
- `eating_mutex`: protect `meals_eaten` counters
- `end_mutex`: protect `end_flag`

## Lifecycle Flow
1. Parse and validate input
2. Allocate philosophers and fork mutex array
3. Assign circular fork pointers (left = i, right = (i + 1) % N)
4. Initialise philosopher threads + one supervisor thread
5. Philosophers loop:
   - Try to take forks
   - Eat (`time_to_eat`), update `last_meal_time`, increment `meals_eaten`
   - Release forks → sleep (`time_to_sleep`) → think
6. Supervisor loop:
   - For each philosopher: check starvation (`current_time - last_meal_time >= time_to_die`)
   - Count how many reached `meal_goal`
   - Set `end_flag` and log death or completion
7. Join threads, destroy mutexes, free memory

## Deadlock Avoidance Strategy
Fork locking order alternates implicitly: all philosophers except the last lock `left` then `right`; the last philosopher locks `right` then `left`. This breaks the cyclic wait condition, preventing classical deadlock.

## Edge Cases Handled
- Single philosopher (`N == 1`): exits early (cannot eat with one fork) with immediate death log.
- Non-numeric input → rejection.
- Zero / negative values → rejection with thematic messages.
- Integer overflow during parse guarded by custom `ft_atoi` returning boundary indicators.

## Testing Ideas
- Survival test: `./philo 5 800 200 200` (should run until a death occurs)
- Meal goal test: `./philo 5 800 200 200 3` (should end cleanly after all eat 3 times)
- Tight timing: `./philo 5 310 100 100` (should show occasional deaths if timing marginal)
- Edge invalid: `./philo 1 800 200 200` (handled early)
- Overflow attempt: very large numeric arguments
