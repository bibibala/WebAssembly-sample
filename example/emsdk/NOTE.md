**Language**: [English](#) | [中文](NOTE.zh.md)

---

When using **Emscripten SDK (emsdk)** to compile C/C++ to WebAssembly, Emscripten provides many tools and macros to control the export and behavior of functions and variables. Here are the commonly used methods and macros similar to `EMSCRIPTEN_KEEPALIVE`:

---

### 1. **`EMSCRIPTEN_KEEPALIVE`**

Ensures that functions or variables are not optimized away during compilation and are exported as part of the WebAssembly module for JavaScript to call.

#### Usage Example:

```cpp
#include <emscripten.h>

EMSCRIPTEN_KEEPALIVE
int add(int a, int b) {
    return a + b;
}
```

When using, you need to call through the WebAssembly instance's `Module`, for example:

```javascript
Module._add(1, 2) // Output: 3
```

---

### 2. **`EXPORT_NAME`**

Sets the name of the generated WebAssembly module, used for naming during JavaScript initialization.

#### Usage Example:

```bash
emcc your_code.cpp -s EXPORT_NAME="MyModule" -o your_code.js
```

Then load in JavaScript:

```javascript
MyModule().then(instance => {
  console.log(instance._add(1, 2))
})
```

---

### 3. **`EXPORTED_FUNCTIONS`**

Explicitly specifies the list of functions to be exported, preventing functions from being optimized away due to non-use.

#### Usage Example:

Add parameters during compilation:

```bash
emcc your_code.cpp -s EXPORTED_FUNCTIONS="['_add', '_subtract']" -o your_code.js
```

Emscripten will ensure these functions are exported and callable through JavaScript:

```javascript
Module._add(1, 2) // Call the exported `add` function
```

---

### 4. **`EMSCRIPTEN_BINDINGS`**

Export C++ classes, functions, or variables through Emscripten's **embind** tool, making them interact with JavaScript in a more natural way.

#### Usage Example:

```cpp
#include <emscripten/bind.h>

int add(int a, int b) {
    return a + b;
}

EMSCRIPTEN_BINDINGS(my_module) {
    emscripten::function("add", &add);
}
```

Use in JavaScript:

```javascript
import Module from "./your_code.js"

Module().then(instance => {
  console.log(instance.add(1, 2)) // Output 3
})
```

---

### 5. **`MAIN_MODULE` and `SIDE_MODULE`**

Used for modular development, allowing multiple WebAssembly modules to be linked and dynamically loaded.

- **`MAIN_MODULE`:** Defines the main module.
- **`SIDE_MODULE`:** Defines side modules for loading by the main module.

#### Usage Example:

Compile main module:

```bash
emcc main.cpp -o main.js -s MAIN_MODULE=1
```

Compile side module:

```bash
emcc side.cpp -o side.wasm -s SIDE_MODULE=1
```

Load side module in main module:

```javascript
Module.loadDynamicLibrary("side.wasm", { global: true, nodelete: true })
```

---

### 6. **`ALLOW_MEMORY_GROWTH`**

Allows WebAssembly memory to grow dynamically, preventing runtime crashes due to insufficient memory.

#### Usage Example:

```bash
emcc your_code.cpp -s ALLOW_MEMORY_GROWTH=1 -o your_code.js
```

---

### 7. **`MODULARIZE`**

Wraps the generated module in a function, making it dynamically loadable through `import`.

#### Usage Example:

```bash
emcc your_code.cpp -s MODULARIZE=1 -o your_code.js
```

In JavaScript:

```javascript
import Module from "./your_code.js"

Module().then(instance => {
  console.log(instance._add(1, 2))
})
```

---

### 8. **`ASYNCIFY`**

Used to support asynchronous operations, such as handling `await` or callbacks.

#### Usage Example:

```bash
emcc your_code.cpp -s ASYNCIFY -o your_code.js
```

C++ code:

```cpp
#include <emscripten.h>
#include <chrono>
#include <thread>

EMSCRIPTEN_KEEPALIVE
void asyncFunction() {
    std::this_thread::sleep_for(std::chrono::seconds(2));
    EM_ASM({ console.log("Async complete"); });
}
```

In JavaScript:

```javascript
Module._asyncFunction()
```

---

### 9. **`EM_ASM` and `EM_JS`**

Used to directly embed JavaScript code in C/C++.

#### **`EM_ASM`**

Embed simple JavaScript code.

```cpp
#include <emscripten.h>

void callJs() {
    EM_ASM({
        console.log("Hello from C++!");
    });
}
```

#### **`EM_JS`**

Embed JavaScript code with return values.

```cpp
#include <emscripten.h>

EM_JS(int, getNumber, (), {
    return 42;
});
```

---

### 10. **`FETCH`**

Supports asynchronous loading of files or data.

#### Usage Example:

```bash
emcc your_code.cpp -o your_code.js -s FETCH=1
```

C++ code:

```cpp
#include <emscripten/fetch.h>

void download(const char* url) {
    emscripten_fetch_t* fetch = emscripten_fetch(EMSCRIPTEN_FETCH_LOAD_TO_MEMORY, url);
    emscripten_fetch_close(fetch);
}
```

---

### Summary

| **Feature**          | **Method/Macro**             | **Purpose**                                |
| -------------------- | ---------------------------- | ------------------------------------------ |
| Export functions/variables | `EMSCRIPTEN_KEEPALIVE`       | Export functions/variables, prevent optimization. |
| Explicitly specify exported functions | `EXPORTED_FUNCTIONS`         | Explicitly export specified functions.     |
| Set module name      | `EXPORT_NAME`                | Set WebAssembly module name.              |
| Bind C++ with JS     | `EMSCRIPTEN_BINDINGS`        | Use embind to export classes, functions, variables. |
| Dynamic module loading | `MAIN_MODULE`, `SIDE_MODULE` | Support modular development, load multiple WebAssembly modules. |
| Dynamic memory growth | `ALLOW_MEMORY_GROWTH`        | Allow WebAssembly memory to grow dynamically. |
| Wrap module as function | `MODULARIZE`                 | Wrap module as dynamic loading function.  |
| Async support        | `ASYNCIFY`                   | Support asynchronous operations (like `await`). |
| Embed JS code        | `EM_ASM`, `EM_JS`            | Directly embed JavaScript code in C++.    |
| File/data async loading | `FETCH`                      | Support asynchronous loading of files or data. |

Through these methods and macros, you can precisely control Emscripten's behavior, making interactions between C/C++ and JavaScript/WebAssembly more efficient.
