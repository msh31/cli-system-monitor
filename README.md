# System monitor
a simpler version of a task manager in cli form, it simply loads the thresholds for cpu & ram usage and process count from a json,
then gets those values from the system and checks if they are above the thresholds

---

## Note:
This utility is Windows only as most of my knowledge about OS' is from Windows when it comes to the programming side

## Build & Run
Requirements:
  - Windows 10/11
  - C++ 17+ compatible compiler (MSVC, GCC, or Clang)
  - CMake 3.20+

```bash
cmake -S . -B build
cmake --build build

../Debug/system-monitor.exe

## or in release
cmake --build build --config release
../Release/system-monitor.exe
```

## Example ouput
```bash
[19:24:46] ALERT: Process count at: 479 (threshold: 400)
[19:24:48] ALERT: CPU usage at: 97.538948% (threshold: 90.000000%)
[19:24:48] ALERT: RAM usage at: 28241MB (threshold: 8192MB)
```
