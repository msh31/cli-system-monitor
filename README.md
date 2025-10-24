# System monitor
a simpler version of a task manager in cli form

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
