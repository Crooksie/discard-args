# discard-args

A C++17 header-only library demonstrating Template Metaprogramming (TMP) techniques for adapting function signatures on the fly.

> **Note:** This project is an exploration of what *can* be done with C++ templates, rather than a recommendation of what *should* be done in production code. It serves as an example of template metaprogramming for demonstration and educational purposes.

## Overview

`discard-args` allows you to wrap existing functions to match different signatures by discarding unwanted parameters, remapping indices, or providing default values for missing arguments - all at compile-time with minimal runtime overhead.

## Features

- **Parameter Discarding**: Wrap a function that takes no arguments so it can be used where arguments are provided.
- **Parameter Mapping**: Selectively map specific arguments from a caller to the target function's parameters.
- **Argument Injection**: Call functions with their default-constructed arguments when the caller provides no parameters.
- **Header-only**: Easy to integrate into any C++17 project.

## Examples

### 1. Discarding All Inputs
When you have a callback that receives arguments you don't need:

```cpp
#include <discard_args.h>

void myHandler() {
    // I don't need the (int x, int y) provided by the caller
}

// Adapt myHandler to accept (int, int) and discard them
auto adapted = adapt<myHandler>().to<int, int>().discard_inputs();

adapted(10, 20); // Calls myHandler()
```

### 2. Selective Parameter Mapping
When you only need a subset or a different order of arguments:

```cpp
#include <discard_args.h>

void myHandler(int x, int y) {
    // Uses x and y
}

// Caller provides (int x, int y, std::string name)
// Map index 0 and 1 to our handler
auto adapted = adapt<myHandler>().to<int, int, std::string>().map<0, 1>();

adapted(1, 2, "ignored"); // Calls myHandler(1, 2)
```

### 3. No-Args Adaptation
When you want to call a function that requires arguments from a context that provides none (uses default-constructed values):

```cpp
#include <discard_args.h>

void myHandler(int x, int y) {
    // ...
}

// Adapt to be called with no arguments
auto adapted = adapt<myHandler>().no_args();

adapted(); // Calls myHandler(0, 0)
```

## Integration

Since this is a header-only library, simply include `include/discard_args.h` in your project.

```cmake
include_directories(include)
```

## Requirements

- C++17 compatible compiler (uses `std::tuple`, `std::apply`, and fold expressions).
