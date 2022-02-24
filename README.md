# fibo

This is a simple C++ package that shows the use of `vcpkg` manifests, a cmake-based toolchain driving tests, and lightly exercises some modern C++ libraries.

## Collect a trace

```
sudo perf record build/src/fibo
```