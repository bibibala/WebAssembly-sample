**Language**: [English](#) | [中文](NOTE.zh.md)

---

Cheerp provides some special attributes (such as `[[cheerp::jsexport]]`) to support exporting from C++ to JavaScript interaction. These attributes allow developers to fine-tune the behavior of exported functions, classes, variables, or objects.

---

### 1. **`[[cheerp::jsexport]]`**

Used to export C++ functions, variables, classes, or methods to JavaScript, making them directly callable from JavaScript.

#### Usage Example:

```cpp
#include <cheerp/clientlib.h>

// Export regular function
[[cheerp::jsexport]]
int add(int a, int b) {
    return a + b;
}

// Export global variable
[[cheerp::jsexport]]
int globalValue = 42;

// Export class
class [[cheerp::jsexport]] MyClass {
public:
    int value;
    MyClass(int v) : value(v) {}

    [[cheerp::jsexport]] int getValue() const {
        return value;
    }

    [[cheerp::jsexport]] void setValue(int v) {
        value = v;
    }
};
```

---

### 2. **`[[cheerp::genericjs]]`**

Converts C++ functions to pure JavaScript functions rather than WebAssembly. These functions are completely implemented in JavaScript and are mainly used for code that needs to directly manipulate the DOM or run in the JavaScript runtime.

#### Usage Example:

```cpp
#include <cheerp/clientlib.h>

// Used for JavaScript interaction, e.g., DOM manipulation
[[cheerp::genericjs]]
void logToConsole(const char* msg) {
    client::console.log(msg);
}
```

---

### 3. **`[[cheerp::wasm]]`**

Marks functions that need to be compiled to WebAssembly. Suitable for performance-critical code.

#### Usage Example:

```cpp
#include <cheerp/clientlib.h>

// This function is forced to compile to WebAssembly
[[cheerp::wasm]]
int multiply(int a, int b) {
    return a * b;
}
```

---

### 4. **`[[cheerp::noinline]]`**

Prevents functions from being inlined. Used when debugging or when functions need to be clearly separated.

#### Usage Example:

```cpp
[[cheerp::noinline]]
int calculate(int a, int b) {
    return a + b;
}
```

---

### 5. **`[[cheerp::dontinline]]`**

Similar to `[[cheerp::noinline]]`, ensures functions are not inlined, usually used to ensure function boundaries exist.

#### Usage Example:

```cpp
[[cheerp::dontinline]]
int subtract(int a, int b) {
    return a - b;
}
```

---

### 6. **`[[cheerp::static]]`**

Used to force member functions or variables to be exported as static.

#### Usage Example:

```cpp
class [[cheerp::jsexport]] Utility {
public:
    [[cheerp::static]]
    static int add(int a, int b) {
        return a + b;
    }
};
```

---

### 7. **`[[cheerp::client]]`**

Specifies that functions or objects exist in the JavaScript environment (e.g., `window` or `document`).

#### Usage Example:

```cpp
#include <cheerp/client.h>

// Access JavaScript's `document` object
client::Document* doc = client::document;

// Define a JavaScript function
[[cheerp::client]]
void alertMessage(const char* msg) {
    client::alert(msg);
}
```

---

### 8. **`[[cheerp::main]]`**

Specifies the program's entry point (`main`), usually used for generating WebAssembly.

#### Usage Example:

```cpp
[[cheerp::main]]
int main() {
    return 0;
}
```

---

### 9. **`[[cheerp::wasm_only]]`**

Marks the entire module to generate only WebAssembly, disabling JavaScript generation.

#### Usage Example:

```cpp
#include <cheerp/clientlib.h>

// Module is completely compiled to WebAssembly
[[cheerp::wasm_only]]
int fastCompute(int a, int b) {
    return a * b;
}
```

---

### Summary

| Attribute                | Description                                                 |
| ------------------------ | ----------------------------------------------------------- |
| `[[cheerp::jsexport]]`   | Export functions, variables, classes, or methods to JavaScript. |
| `[[cheerp::genericjs]]`  | Convert C++ functions to pure JavaScript functions.        |
| `[[cheerp::wasm]]`       | Force functions to be compiled to WebAssembly.             |
| `[[cheerp::noinline]]`   | Prevent functions from being inlined.                      |
| `[[cheerp::dontinline]]` | Prevent functions from being inlined, similar to `[[cheerp::noinline]]`. |
| `[[cheerp::static]]`     | Export static member functions or variables.               |
| `[[cheerp::client]]`     | Specify objects or functions in the JavaScript environment. |
| `[[cheerp::main]]`       | Specify the program's entry point.                         |
| `[[cheerp::wasm_only]]`  | Force the entire module to generate only WebAssembly, no JavaScript. |

These attributes can be used in combination as needed to optimize performance or control export behavior.
