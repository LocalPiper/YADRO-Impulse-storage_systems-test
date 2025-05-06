# Club Simulator

A C++ program that simulates the behavior of a club with multiple tables and a waiting queue. Clients can enter, take seats, wait, and leave based on specified rules and constraints.

## 🛠 Build & Run

### Prerequisites

- Ubuntu (any Linux distro should be fine: project was built on Pop!OS)
- C++17 compiler `g++`
- `make`

### Build

```
make
```

Or manually:

```
g++ -std=c++17 -I. -o main main.cpp club.cpp interpreter.cpp printer.cpp util.cpp
```

### Run

```
./main input.txt
```

## 📥 Input Format

Input should be provided via file in the following format:

```
<number_of_tables>
<opening_time> <closing_time>
<cost_per_hour>
<event_1>
<event_2>
...
```

Each event line represents a client action:

```
<HH:MM> <event_type> <client_name> [<table_number>]
```

- `event_type`:
  - `1` – Client enters
  - `2` – Client takes a table
  - `3` – Client waits in queue
  - `4` – Client leaves
- `table_number` is only required for event type `2`

### Example:

```
10
10:00 20:00
100
10:05 1 alice
10:10 2 alice 5
10:15 1 bob
10:20 3 bob
10:30 4 alice
10:35 2 bob 5
```

## 📤 Output

The output is printed to `stdout` and includes both successful actions and error messages for invalid operations.

---
