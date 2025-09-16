# Philosophers (Dining Philosophers Problem)

## Theoretical Background
The Dining Philosophers problem, introduced by Edsger Dijkstra, models a classic concurrency challenge: multiple autonomous processes (philosophers) compete for a finite set of shared, indivisible resources (forks) arranged in a cyclic dependency. Each philosopher alternates between thinking and eating; to eat they must hold both adjacent forks. The problem illustrates risks of:
- Deadlock (all hold one fork and wait forever)
- Starvation (one never acquires both forks)
- Livelock (processes keep reacting without progress)
- Resource contention and scheduling fairness

It is commonly used to teach techniques such as resource ordering, arbitration, and monitoring for progress guarantees. This implementation applies an asymmetric fork acquisition order to break the circular wait condition—one of Coffman’s deadlock conditions—while a supervisor thread detects starvation (death) and goal completion. For further theoretical context see the Wikipedia article: https://en.wikipedia.org/wiki/Dining_philosophers_problem

A multithreaded C implementation of the classic Dining Philosophers synchronization problem, developed as part of the 42 curriculum. The project focuses on precise timing, thread lifecycle management, deadlock avoidance, and data‑race prevention using POSIX threads (`pthread`).

## 🎯 Goal
Simulate a set of philosophers sitting at a round table who alternately think, eat, and sleep while sharing a limited number of forks (one between each pair). The challenge is to coordinate access to forks so that no philosopher starves and data remains consistent, while respecting strict timing constraints.

## ✅ Features
- POSIX threads for each philosopher + a dedicated supervisor thread
- Deterministic fork acquisition order to avoid deadlock
- Fine-grained mutexes: forks + print + meal time + meal counters + end flag
- Timing in milliseconds using `gettimeofday`
- Graceful termination when:
  - A philosopher dies (exceeds `time_to_die` since last meal)
  - All philosophers reach the optional meal goal
- Colorized log output with timestamps
- Input validation with edge‑case handling

## 🧪 CLI Usage
```
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [meal_goal]
```
All time arguments are in milliseconds.

| Argument | Description | Constraints |
|----------|-------------|-------------|
| `number_of_philosophers` | Total philosophers / forks | > 1 |
| `time_to_die` | Max time a philosopher can go without eating | > 0 |
| `time_to_eat` | Time spent eating (holding both forks) | > 0 |
| `time_to_sleep` | Time spent sleeping | > 0 |
| `meal_goal` *(optional)* | Each philosopher must eat this many times before sim ends | > 0 (if provided) |

If `meal_goal` is omitted, simulation runs until a death occurs.

### Example
```
./philo 5 800 200 200 7
```
Runs 5 philosophers; each must eat 7 times or simulation ends sooner if one dies.

## 🧵 Thread & Data Model

| Component | Purpose |
|-----------|---------|
| `t_given` | Global immutable & shared runtime parameters + shared mutexes + timing + end flag |
| `t_philo` | Per‑philosopher state: id, fork pointers, last meal timestamp, meals eaten |
| Philosopher threads | Execute the `routine`: eat → sleep → think loop until termination |
| Supervisor thread | Periodically checks for death or goal satisfaction |

### Synchronization Primitives
- `fork` mutexes: one per philosopher (circular array)
- `print_mutex`: serialize console output (prevent interleaving)
- `time_mutex`: protect `last_meal_time` updates/reads
- `eating_mutex`: protect `meals_eaten` counters
- `end_mutex`: protect `end_flag`

## 🔄 Lifecycle Flow
1. Parse & validate input → initialize `t_given`
2. Allocate philosophers & fork mutex array
3. Assign circular fork pointers (left = i, right = (i+1)%N)
4. Spawn philosopher threads + one supervisor thread
5. Philosophers loop:
   - Try to take forks (ordered locking scheme to avoid deadlock)
   - Eat (`time_to_eat`), update `last_meal_time`, increment `meals_eaten`
   - Release forks → sleep (`time_to_sleep`) → think (short pause)
6. Supervisor loop:
   - For each philosopher: check starvation (`current_time - last_meal_time >= time_to_die`)
   - Count how many reached `meal_goal`
   - Set `end_flag` and log death or completion
7. Main thread joins all threads, destroys mutexes, frees memory

## 🛡️ Deadlock Avoidance Strategy
Fork locking order alternates implicitly: all philosophers except the last lock `left` then `right`; the last philosopher locks `right` then `left`. This breaks the cyclic wait condition, preventing classical deadlock.

## ⏱️ Timing
- Millisecond precision via `gettimeofday`
- Relative timestamps printed from a captured `start_time`
- Minimal active waiting; `usleep` used for state durations
- Supervisor sleeps for 10ms between scans to reduce overhead

## 📄 Logging Format
```
<ms_since_start> <philo_id> <action>
```
Actions: `has taken a fork`, `is eating`, `is sleeping`, `is thinking`, `died`.
Color codes highlight states (death in orange, etc.).

## ⚙️ Build Instructions
Requirements: POSIX system (macOS/Linux), `cc` compiler.

Build:
```
make
```
Binary output: `./bin/philo`

Clean object files:
```
make clean
```
Full rebuild:
```
make re
```
Remove binary directory:
```
make fclean
```

## 🧠 Design Choices & Rationale
- Separate supervisor thread: avoids adding extra checks inside each philosopher loop; centralizes termination logic.
- Multiple specialized mutexes instead of one global: reduces contention (printing vs. eating vs. timing).
- Timestamp stored per philosopher and updated only after successful eating cycle.
- Optional `meal_goal` uses `INT_MAX` sentinel when absent → simplifies comparison logic.
- Lightweight thinking delay (`usleep(1000)`) to prevent aggressive busy looping and encourage fork turnover.

## 🔍 Edge Cases Handled
- Single philosopher (`N == 1`): exits early (cannot eat with one fork) with immediate death log.
- Non-numeric input → rejection.
- Zero / negative values → rejection with thematic messages.
- Integer overflow during parse guarded by custom `ft_atoi` returning boundary indicators.

## 🚫 Known Limitations / Potential Improvements
- No active fairness: a philosopher could still get less CPU/forks under extreme scheduling conditions.
- Supervisor sleep interval (10ms) may delay death detection slightly for very small `time_to_die` values.
- No adaptive backoff when contended.
- No protection against extremely large philosopher counts impacting startup time / memory.

### Future Enhancements
- Add precise busy-wait micro-sleeper for short intervals to improve timing accuracy under <10ms constraints.
- Introduce starvation prevention (e.g., ticketing or priority rotation).
- Provide CLI flag for different fork acquisition strategies to benchmark behavior.
- Add unit tests & stress harness (randomized timings, extreme values).
- Export structured logs (JSON) for visualization / metrics.

## 🧪 Testing Ideas
- Survival test: `./philo 5 800 200 200` (should run until a death occurs)
- Meal goal test: `./philo 5 800 200 200 3` (should end cleanly after all eat 3 times)
- Tight timing: `./philo 5 310 100 100` (should show occasional deaths if timing marginal)
- Edge invalid: `./philo 1 800 200 200` (handled early)
- Overflow attempt: very large numeric arguments

## 🗂️ Code Map
| File | Purpose |
|------|---------|
| `philo.c` | Entry point: parse, init, launch, cleanup |
| `parsing.c` | Input validation & parameter initialization |
| `forks.c` | Fork mutex allocation & assignment |
| `threads.c` | Thread creation & joining logic |
| `routine.c` | Philosopher main behavior loop |
| `eating.c` | Fork acquisition + eating sequence |
| `supervisor.c` | Monitoring for death / completion |
| `utils.c` | Timing, logging, cleanup helpers |
| `ft_atoi.c` | Safe integer parsing with overflow checks |
| `include/philo.h` | Shared type + function declarations |

## 🧾 License
Educational project (42 school). If you wish to reuse or extend, feel free to fork and adapt with attribution.

## 🙋 Author
Implemented by a 42 student as part of the philosophers project. Portfolio-ready demonstration of multithreading fundamentals, synchronization design, and careful resource management in C.

---
Feel free to reach out for collaboration or feedback.
